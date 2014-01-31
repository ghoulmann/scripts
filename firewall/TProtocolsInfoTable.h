#ifndef FIREWALL_TPROTOCOLSINFOTABLE_H
#define FIREWALL_TPROTOCOLSINFOTABLE_H

#include <memory>

#include <QStringList>

#include "GenericParser.h"

class QTextStream;

typedef QStringList TProtocolNames;
void operator>>(const TStrFields &StrFields, TProtocolNames &ProtocolNames);

enum class TPortType { TCP, UDP, LAST };
inline uint qHash(const TPortType &t, uint seed)
   { typedef std::underlying_type<TPortType>::type TUT; return qHash(static_cast<TUT>(t), seed); }

QDebug operator<<(QDebug Out, TPortType PortType);

typedef QSet<int> TPorts;

typedef QHash<TPortType, TPorts> TPortsInfo;
void operator>>(const TStrFields &StrFields, TPortsInfo &PortsInfo);

struct TProtocolInfo
   {
      TProtocolNames ProtocolNames;
      TPortsInfo IncomingPorts;
      TPortsInfo OutcomingPorts;
   };
QDebug operator<<(QDebug Out, const TProtocolInfo &ProtocolInfo);
void operator>>(const TStrColumns &StrColumns, TProtocolInfo &ProtocolInfo);
typedef std::shared_ptr<TProtocolInfo> TProtocolInfoPtr;

typedef QHash<QString, TProtocolInfoPtr> TProtocolsInfoTable;
void operator>>(const TStrRows &StrRows, TProtocolsInfoTable &ProtocolsInfoTable);
QDebug Out(QDebug Out, const TProtocolsInfoTable &ProtocolsInfoTable);

#endif // FIREWALL_TPROTOCOLSINFOTABLE_H
