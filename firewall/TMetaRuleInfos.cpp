#include "TMetaRuleInfos.h"

#include <QRegularExpression>

#include "EvManGlobal.h"


QDebug operator<<(QDebug Out, TAction Action)
   {
      typedef std::underlying_type<TAction>::type TUT;
      static const TUT MAX = static_cast<TUT>(TAction::LAST);
      static const std::array<const char *, MAX> Str = { { "Accept", "Drop", "Log" } };
      const TUT N = static_cast<TUT>(Action);
      if(N > MAX)
         {
            Out << "UnknownAction";
            return Out;
         }
      return Out << QString(Str[N]);
   }


QString ParseSubject(QString String)
   {
      String.remove(QRegularExpression("\\(.*$")); // Remove all starting with (
      String.remove(QRegularExpression("^[ \t]*")); // Remove leading spaces
      String.remove(QRegularExpression("[ \t]*$")); // Remove last spaces
      if(String.contains("*"))
         {
            ASSERT(String.size() == 1);
            String.clear();
         }
      return String;
   }
TActions ParseActions(const QString &String)
   {
      TActions Result;

      if(String.contains("("))
         ASSERT_X(String.contains(")"), "String" << String << "contains \"(\", but does not contain \")\" !");

      if(!String.contains("("))
         {
            Result << TAction::Accept;
            return Result;
         }

      QRegularExpression Re("\\(.*?\\)");
      QRegularExpressionMatchIterator MatchIt = Re.globalMatch(String);
      ASSERT(MatchIt.isValid());
      ASSERT(MatchIt.hasNext());
      QRegularExpressionMatch Match = MatchIt.next();
      ASSERT(!MatchIt.hasNext());

      QString Temp = Match.captured();
      ASSERT_OP(Temp[0], ==, QChar('('));
      ASSERT_OP(Temp[Temp.size() - 1], ==, QChar(')'));
      Temp.remove(0, 1);
      Temp.remove(Temp.size() - 1, 1);
      const QStringList &StrActions = Temp.split(" ");

      for(const QString &StrAction: StrActions)
         {
            if(StrAction.compare("L", Qt::CaseInsensitive) == 0)
               Result << TAction::Log;
            else if(StrAction.compare("-") == 0)
               Result << TAction::Drop;
            else
               ASSERT_X(false, "Unknown straction:" << StrAction << "I know only about \"L\" (log) and \"-\" (drop)!");
         }

      return Result;
   }

void operator>>(const QString &String, TSubjectInfo &SubjectInfo)
   {
      SubjectInfo.Subject = ParseSubject(String);
      SubjectInfo.Actions = ParseActions(String);
   }

// bad.server (L -), hz(L), good, *, a(L)(L)
void operator>>(const TStrFields &StrFields, TSubjectsInfo &SubjectsInfo)
   {
      SubjectsInfo.clear();
      for(const QString &String: StrFields)
         {
            if(String.isEmpty())
               continue;
            TSubjectInfo SubjectInfo;
            String >> SubjectInfo;
            SubjectsInfo << SubjectInfo;
         }
   }
QDebug operator<<(QDebug Out, const TSubjectInfo &SubjectInfo)
   {
      Out << "Subject: " << SubjectInfo.Subject << ", Actions: " << SubjectInfo.Actions;
      return Out;
   }


void ParseProcessNames(const TStrFields &StrFields, TProcessNames &ProcessNames)
   {
      ProcessNames.clear();

      ASSERT_X_OP(StrFields.size(), >, 0,
                  "In StrFields: " << StrFields << "in TProcessNames column must be at least \"*\" symbol");
      ASSERT_X_OP(StrFields[0].size(), >, 0, "In StrFields: " << StrFields
                                          << "in TProcessNames column must be at least \"*\" symbol,"
                                          << "actually:" << StrFields[0]);
      if(StrFields[0] == "*")
         {
            ASSERT_X_OP(StrFields.size(), ==, 1, "If you specify \"*\" as process name, then it means \"all processes\""
                                                 << "and if so, why do you specify something else?");
            return;
         }
      for(const QString &String: StrFields)
         {
            ASSERT_X_OP(String, !=, "*", "If you specify \"*\" as process name, then it means \"all processes\""
                                          << "and if so, why do you specify something else?");
            ProcessNames << String;
         }
   }

void ParseUserNames(const TStrFields &StrFields, TUserNames &UserNames)
   {
      UserNames.clear();

      ASSERT_X_OP(StrFields.size(), >, 0,
                  "In StrFields: " << StrFields << "in TUserNames column must be at least \"*\" symbol");
      ASSERT_X_OP(StrFields[0].size(), >, 0, "In StrFields: " << StrFields
                                          << "in TUserNames column must be at least \"*\" symbol,"
                                          << "actually:" << StrFields[0]);
      if(StrFields[0] == "*")
         {
            ASSERT_X_OP(StrFields.size(), ==, 1, "If you specify \"*\" as user name, then it means \"all users\""
                                                 << "and if so, why do you specify something else?");
            return;
         }
      for(const QString &String: StrFields)
         {
            ASSERT_X_OP(String, !=, "*", "If you specify \"*\" as user name, then it means \"all users\""
                                          << "and if so, why do you specify something else?");
            UserNames << String;
         }
   }

QDebug operator<<(QDebug Out, const TMetaRuleInfo &MetaRuleInfo)
   {
      Out << "TMetaRuleInfo(\n";

      Out << "ProtocolNames: "       << MetaRuleInfo.ProtocolNames
          << "\t" << "InputRules:"   << MetaRuleInfo.InputRules
          << "\t" << "OutputRules:"  << MetaRuleInfo.OutputRules
          << "\t" << "ProcessNames:" << MetaRuleInfo.ProcessNames
          << "\t" << "UserNames:"    << MetaRuleInfo.UserNames;
      Out << ")";
      return Out;
   }

void operator>>(const TStrColumns &StrColumns, TMetaRuleInfo &MetaRuleInfo)
   {
      ASSERT_X(StrColumns.size() == 5, "StrColumns:" << StrColumns << "has" << StrColumns.size() << ", but must have 5!");
      StrColumns[0] >> MetaRuleInfo.ProtocolNames;
      StrColumns[1] >> MetaRuleInfo.InputRules;
      StrColumns[2] >> MetaRuleInfo.OutputRules;
      ParseProcessNames(StrColumns[3], MetaRuleInfo.ProcessNames);
      ParseUserNames(StrColumns[4], MetaRuleInfo.UserNames);
   }

void operator>>(const TStrRows &StrRows, TMetaRuleInfos &MetaRuleInfos)
   {
      MetaRuleInfos.clear();
      for(const TStrColumns &StrColumns: StrRows)
         {
            TMetaRuleInfo MetaRuleInfo;
            StrColumns >> MetaRuleInfo;
            MetaRuleInfos << MetaRuleInfo;
         }
   }

QDebug Out(QDebug Out, const TMetaRuleInfos &MetaRuleInfos)
   {
      Out << "TMetaRuleInfos(\n";

      for(const TMetaRuleInfo &MetaRuleInfo: MetaRuleInfos)
         Out << MetaRuleInfo << "\n";

      Out << ")";
      return Out;
   }
