#ifndef FIREWALL_TRULE_H
#define FIREWALL_TRULE_H

#include "TMetaRuleInfos.h"

enum class TDirection { Input, Output, LAST };
QDebug operator<<(QDebug Out, TDirection Direction);

struct TRule
   {
      QString ProcessName;
      QString UserName;
      QString Host;
      TDirection Direction;
      TPorts Ports;
      TPortType PortType;
      TActions Actions;
   };
QDebug operator<<(QDebug Out, TRule Rule);
typedef QVector<TRule> TRules;

TRules GenerateRules(const TProtocolsInfoTable &ProtocolsInfoTable, const TMetaRuleInfos &MetaRuleInfos);

#endif // FIREWALL_TRULE_H
