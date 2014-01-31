#ifndef FIREWALL_TRULE_H
#define FIREWALL_TRULE_H

#include "TMetaRuleInfos.h"

enum class TDirection { Input, Output };

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

typedef QVector<TRule> TRules;

TRules GenerateRules(const TProtocolsInfoTable &ProtocolsInfoTable, const TMetaRuleInfos &MetaRuleInfos);

#endif // FIREWALL_TRULE_H
