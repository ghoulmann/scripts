#include <memory>

#include <iostream>
#include <QFile>

#include "GenericParser.h"
#include "EvManGlobal.h"
#include "TProtocolsInfoTable.h"
#include "TMetaRuleInfos.h"
#include "TRule.h"
#include "TBackends.h"

const QString BACKEND_OPTION = "--backend=";
const QString DEFAULT_BACKEND = "ip";

QStringList ParseBackends(QString Argument)
   {
      Argument.remove(BACKEND_OPTION, Qt::CaseInsensitive);
      return Argument.split(',');
   }
QTextStream *CreateTextStream(QFile &File, const QString &Argument)
   {
      File.setFileName(Argument);
      const bool Ok = File.open(QFile::ReadOnly);
      ASSERT(Ok);
      return new QTextStream(&File);
   }

int main(int argc, char **argv)
   {
      std::unique_ptr<QTextStream> Stream;
      QFile ConfigFile;
      QStringList Backends;

      if(argc == 1)
         {
            Stream = std::unique_ptr<QTextStream>(new QTextStream(stdin, QIODevice::ReadOnly));
            Backends << DEFAULT_BACKEND;
         }
      else if(argc == 2)
         {
            const QString &FirstArg = argv[1];
            if(FirstArg.startsWith(BACKEND_OPTION))
               Backends = ParseBackends(FirstArg);
            else
               Stream = std::unique_ptr<QTextStream>(CreateTextStream(ConfigFile, FirstArg));
         }
      else if(argc == 3)
         {
            const QString &FirstArg = argv[1];
            const QString &SecondArg = argv[2];
            Stream = std::unique_ptr<QTextStream>(CreateTextStream(ConfigFile, FirstArg));
            ASSERT_X(SecondArg.startsWith(BACKEND_OPTION), "What it your second option?:" << SecondArg
                     << "It must starts with " << BACKEND_OPTION << " and denote used backends"
                     << "available ones are ip, ip6, nf");
            Backends = ParseBackends(FirstArg);
         }
      else
         ASSERT_X(false, "Too many options!");

      const TStrRows &StrProtocolInfoTable = Parse(*Stream, 3);
      TProtocolsInfoTable ProtocolsInfoTable;
      StrProtocolInfoTable >> ProtocolsInfoTable;
      //Out(qDebug(), ProtocolsInfoTable);


      const TStrRows &StrRulesInfoTable = Parse(*Stream, 5);
      TMetaRuleInfos MetaRuleInfos;
      StrRulesInfoTable >> MetaRuleInfos;

      //Out(qDebug(), MetaRuleInfos);

      const TRules &Rules = GenerateRules(ProtocolsInfoTable, MetaRuleInfos);
      //qDebug() << Rules;

      const QStringList &Commands = GenerateCommands(GenerateCommands_Ip, Rules);

      for(const QString &Command: Commands)
         std::cout << Command.toStdString() << std::endl;

      return 0;
   }
