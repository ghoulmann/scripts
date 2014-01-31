#ifndef FIREWALL_TRULESINFOTABLE_H
#define FIREWALL_TRULESINFOTABLE_H

#include "TProtocolsInfoTable.h"

enum class TAction { Accept, Drop, Log, LAST};

typedef QStringList TSubjects;

typedef QHash<TAction, TSubjects> TSubjectsInfo;

typedef QStringList TProcessNames;
typedef QStringList TUserNames;

struct TMetaRuleInfo
   {
      TProtocolNames ProtocolNames;
      TSubjectsInfo InputRules;
      TSubjectsInfo OutputRules;
      TProcessNames ProcessNames;
      TUserNames UserNames;
   };

typedef QVector<TMetaRuleInfo> TMetaRuleInfos;

#endif // FIREWALL_TRULESINFOTABLE_H
