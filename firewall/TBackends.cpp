#include "TBackends.h"

#include "EvManGlobal.h"

//root@Impedance:/home/Void/sys# iptables -A OUTPUT    -p udp    -m multiport --dports 4380,27004,27005,27006,27028,27007,27029,27000,27030,27001,27002,4379,27024,27003,27025,27026,27027,27020,27021,27022,27023,27016,27017,27018,27019,27012,27013,27014,27015,27008,27009,27010,3478,27011        -j ACCEPT
//iptables v1.4.18: too many ports specified
//Try `iptables -h' or 'iptables --help' for more information.
//QString PortsToString(const TPorts &Ports)
//   {
//      QString Result;
//      if(Ports.size() == 1)
//         {
//            Result = "--dport " + QString::number(*Ports.begin());
//            return Result;
//         }
//      Result = "-m multiport --dports ";
//      bool FirstTime = true;
//      for(int Port: Ports)
//         {
//            if(!FirstTime)
//               Result += ",";
//            if(FirstTime)
//               FirstTime = false;
//            Result += QString::number(Port);
//         }
//      return Result;
//   }

QString PortToString(const int Port)
   {
      QString Result = "--dport " + QString::number(Port);
      return Result;
   }


QString ActionToString(const TAction &Action)
   {
      QString Result = "-j ";
      if(Action == TAction::Accept)
         Result += "ACCEPT";
      else if(Action == TAction::Drop)
         Result += "DROP";
      else
         ASSERT_X(false, "Unsupported action:" << Action);

      return Result;
   }
QString DirectionToString(const TDirection &Direction)
   {
      QString Result;
      if(Direction == TDirection::Input)
         Result = "INPUT";
      else if(Direction == TDirection::Output)
         Result = "OUTPUT";
      else
         ASSERT_X(false, "Unsupported direction:" << Direction);

      return Result;
   }

QString PortTypeToString(const TPortType &PortType)
   {
      QString Result = "-p ";
      if(PortType == TPortType::TCP)
         Result += "tcp";
      else if(PortType == TPortType::UDP)
         Result += "udp";
      else
         ASSERT_X(false, "Unsupported port type:" << PortType);

      return Result;
   }

QString HostToString(const TDirection &Direction, const QString &Host)
   {
      QString Result;
      if(Host.isEmpty())
         return Result;

      if(Direction == TDirection::Input)
         Result = "-s ";
      else if(Direction == TDirection::Output)
         Result = "-d ";
      else
         ASSERT_X(false, "Unsupported direction:" << Direction);

      Result += Host;

      return Result;
   }

QStringList GenerateCommands_Ip(const TRule &Rule)
   {
      QStringList Result;
      for(const TAction &Action: Rule.Actions)
         {
            for(const int Port: Rule.Ports)
               {
                  QString Command = "iptables -A " +
                                    DirectionToString(Rule.Direction) + "    " +
                                    PortTypeToString(Rule.PortType) + "    " +
                                    PortToString(Port) + "    " +
                                    HostToString(Rule.Direction, Rule.Host) + "    " +
                                    ActionToString(Action);
                  Result << std::move(Command);
               }
         }
      return Result;
   }

QStringList GenerateCommands(GenerateCommand FPtr, const TRules &Rules)
   {
      QStringList Result;
      for(const TRule &Rule: Rules)
         Result << FPtr(Rule);
      return Result;
   }
