#ifndef FIREWALL_TABSTRACTBACKEND_H
#define FIREWALL_TABSTRACTBACKEND_H

#include "TRule.h"

typedef QStringList (*GenerateCommand)(const TRule &Rule);

QStringList GenerateCommands_Ip(const TRule &Rule);

QStringList GenerateCommands(GenerateCommand FPtr, const TRules &Rules);


#endif // FIREWALL_TABSTRACTBACKEND_H
