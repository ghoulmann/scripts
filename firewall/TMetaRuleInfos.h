#ifndef FIREWALL_TMETARULEINFOS_H
#define FIREWALL_TMETARULEINFOS_H

#include <QSet>

#include "TProtocolsInfoTable.h"


enum class TAction { Accept, Drop, Log, LAST};
QDebug operator<<(QDebug Out, TAction Action);
//inline uint qHash(const TAction &t, uint seed)
//   { typedef std::underlying_type<TAction>::type TUT; return qHash(static_cast<TUT>(t), seed); }


typedef QVector<TAction> TActions;

struct TSubjectInfo
   {
      QString Subject;
      TActions Actions;
   };
QDebug operator<<(QDebug Out, const TSubjectInfo &SubjectInfo);
void operator>>(const QString &String, TSubjectInfo &SubjectInfo);

typedef QVector<TSubjectInfo> TSubjectsInfo;
void operator>>(const TStrFields &StrFields, TSubjectsInfo &SubjectsInfo);

typedef QStringList TProcessNames;
void ParseProcessNames(const TStrFields &StrFields, TProcessNames &ProcessNames);

typedef QStringList TUserNames;
void ParseUserNames(const TStrFields &StrFields, TUserNames &UserNames);

struct TMetaRuleInfo
   {
      TProtocolNames ProtocolNames;
      TSubjectsInfo InputRules;
      TSubjectsInfo OutputRules;
      TProcessNames ProcessNames;
      TUserNames UserNames;
   };
QDebug operator<<(QDebug Out, const TMetaRuleInfo &MetaRuleInfo);
void operator>>(const TStrColumns &StrColumns, TMetaRuleInfo &MetaRuleInfo);

typedef QVector<TMetaRuleInfo> TMetaRuleInfos;
void operator>>(const TStrRows &StrRows, TMetaRuleInfos &MetaRuleInfos);
QDebug Out(QDebug Out, const TMetaRuleInfos &MetaRuleInfos);

#endif // FIREWALL_TMETARULEINFOS_H
