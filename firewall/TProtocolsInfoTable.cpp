#include "TProtocolsInfoTable.h"

#include <QRegularExpression>

#include "EvManGlobal.h"

void operator>>(const TStrFields &StrFields, TProtocolNames &ProtocolNames)
   {
      ASSERT_X_OP(StrFields.size(), >=, 1, "Specify at least one protocol name!");
      ASSERT_X_OP(StrFields[0].size(), >, 0, "Specify at least one protocol name!");
      ProtocolNames = StrFields;
   }

QDebug operator<<(QDebug Out, TPortType PortType)
   {
      typedef std::underlying_type<TPortType>::type TUT;
      static const TUT MAX = static_cast<TUT>(TPortType::LAST);
      static const std::array<const char *, MAX> Str = { { "TCP", "UDP" } };
      const TUT N = static_cast<TUT>(PortType);
      if(N > MAX)
         {
            Out << "UnknownPortType";
            return Out;
         }
      return Out << QString(Str[N]);
   }



void ParsePortTypes(const QString &Str, bool &HasTcp, bool &HasUdp)
   {
      HasTcp = Str.contains("tcp", Qt::CaseInsensitive);
      HasUdp = Str.contains("udp", Qt::CaseInsensitive);
      ASSERT_X(HasTcp || HasUdp, "String" << Str << "does not contain neither \"tcp\", not \"udp\"!");
   }

void ParsePorts(const QString &Str, int &FirstPort, int &SecondPort)
   {
      FirstPort = -1;
      SecondPort = -1;

      QRegularExpression Re("\\d+");
      QRegularExpressionMatchIterator MatchIt = Re.globalMatch(Str);
      ASSERT(MatchIt.isValid());
      ASSERT(MatchIt.hasNext());
      for(; MatchIt.hasNext(); )
         {
            int *Port = nullptr;
            if(FirstPort == -1)
               Port = &FirstPort;
            else if(SecondPort == -1)
               Port = &SecondPort;
            else
               ASSERT_X(false, "How it can be that in the string more than two numbers?");

            QRegularExpressionMatch Match = MatchIt.next();
            bool Ok;
            *Port = Match.captured().toInt(&Ok);
            ASSERT_X(Ok, "Can not parse" << Match.captured() << "as int!");
         }
      if(SecondPort != -1) // This is range => check it
         {
            ASSERT_OP(FirstPort, !=, SecondPort);
            ASSERT_OP(FirstPort, <, SecondPort);
            ASSERT_OP(SecondPort, >, 0);
         }
      ASSERT_OP(FirstPort, >, 0);

   }

TPorts GeneratePortsRange(const int FirstPort, const int SecondPort)
   {
      TPorts Result;
      if(SecondPort == -1)
         {
            Result << FirstPort;
            return Result;
         }
      for(int i = FirstPort; i <= SecondPort; ++i)
         Result << i;
      return Result;
   }

// 27000-27030(udp),
// 27014-27050(tcp),
// 3478(udp),
// 4379(udp), 4380(udp)
void operator>>(const TStrFields &StrFields, TPortsInfo &PortsInfo)
   {
      PortsInfo.clear();
      for(const QString &Str: StrFields)
         {
            if(Str.isEmpty())
               continue;

            bool HasTcp;
            bool HasUdp;
            ParsePortTypes(Str, HasTcp, HasUdp);
            int FirstPort;
            int SecondPort;
            ParsePorts(Str, FirstPort, SecondPort);

            if(HasTcp)
               PortsInfo[TPortType::TCP].unite(GeneratePortsRange(FirstPort, SecondPort));
            if(HasUdp)
               PortsInfo[TPortType::UDP].unite(GeneratePortsRange(FirstPort, SecondPort));
         }
   }

void operator>>(const TStrColumns &StrColumns, TProtocolInfo &ProtocolInfo)
   {
      ASSERT_X(StrColumns.size() == 3, "StrColumns:" << StrColumns << "has" << StrColumns.size() << ", but must have 3!")
      StrColumns[0] >> ProtocolInfo.ProtocolNames;
      StrColumns[1] >> ProtocolInfo.IncomingPorts;
      StrColumns[2] >> ProtocolInfo.OutcomingPorts;
   }

void operator>>(const TStrRows &StrRows, TProtocolsInfoTable &ProtocolsInfoTable)
   {
      ProtocolsInfoTable.clear();

      for(const TStrColumns &StrColumns: StrRows)
         {
            TProtocolInfoPtr ProtocolInfo = TProtocolInfoPtr(new TProtocolInfo);
            StrColumns >> *ProtocolInfo;
            for(const QString &ProtocolName: ProtocolInfo->ProtocolNames)
               {
                  ASSERT_X(!ProtocolsInfoTable.contains(ProtocolName),
                           "ProtocolsInfoTable already contains such protocol name: " << ProtocolName);
                  ProtocolsInfoTable[ProtocolName] = ProtocolInfo;
               }
         }
   }


QDebug operator<<(QDebug Out, const TProtocolInfo &ProtocolInfo)
   {
      Out << "Names: " << ProtocolInfo.ProtocolNames
          << "\t" << "IncomingPorts:" << ProtocolInfo.IncomingPorts
          << "\t" << "OutcomingPorts:" << ProtocolInfo.OutcomingPorts
          << "\n";
      return Out;
   }

QDebug Out(QDebug Out, const TProtocolsInfoTable &ProtocolsInfoTable)
   {
      Out << "TProtocolsInfoTable(\n";
      for(TProtocolsInfoTable::const_iterator It = ProtocolsInfoTable.begin(); It != ProtocolsInfoTable.end(); ++It)
         {
            const QString &ProtocolName = It.key();
            TProtocolInfoPtr ProtocolInfoPtr = It.value();
            Out << ProtocolName << "\n";
            if(!ProtocolInfoPtr)
               Out << "(null)";
            else Out << *ProtocolInfoPtr;
            Out << "\n";
         }
      Out << ")";
      return Out;
   }
