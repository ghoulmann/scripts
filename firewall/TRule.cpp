#include "TRule.h"

#include "EvManGlobal.h"

TRules GenerateRules(const TPortsInfo &PortsInfo,
                     const TSubjectsInfo &SubjectsInfo,
                     TProcessNames ProcessNames,
                     TUserNames UserNames,
                     const TDirection &Direction)
   {
      TRules Result;

      if(ProcessNames.empty())
         ProcessNames << ""; // This needed to enter in for loop by ProcessNames at least once (and generate Rule)
      if(UserNames.empty())
         UserNames << ""; // This needed to enter in for loop by UserNames at least once (and generate Rule)

      for(TPortsInfo::const_iterator PortsInfoIt = PortsInfo.cbegin(); PortsInfoIt != PortsInfo.cend(); ++PortsInfoIt)
         {
            const TPortType &PortType = PortsInfoIt.key();
            const TPorts &Ports = PortsInfoIt.value();
            for(const TSubjectInfo &SubjectInfo: SubjectsInfo)
               {
                  for(const QString &ProcessName: ProcessNames)
                     {
                        for(const QString &UserName: UserNames)
                           {
                              TRule Rule;
                              Rule.ProcessName = ProcessName;
                              Rule.UserName = UserName;
                              Rule.Host = SubjectInfo.Subject;
                              Rule.Direction = Direction;
                              Rule.Ports = Ports;
                              Rule.PortType = PortType;
                              Rule.Actions = SubjectInfo.Actions;
                              Result << std::move(Rule);
                           }
                     }
               }
         }

      return Result;
   }

TRules GenerateRulesForProtocolName(const TProtocolInfo &ProtocolInfo, const TMetaRuleInfo &MetaRuleInfo)
   {
      TRules IncomingRules = GenerateRules(ProtocolInfo.IncomingPorts,
                                           MetaRuleInfo.InputRules,
                                           MetaRuleInfo.ProcessNames,
                                           MetaRuleInfo.UserNames,
                                           TDirection::Input);
      TRules OutcomingRules = GenerateRules(ProtocolInfo.OutcomingPorts,
                                            MetaRuleInfo.OutputRules,
                                            MetaRuleInfo.ProcessNames,
                                            MetaRuleInfo.UserNames,
                                            TDirection::Output);

      TRules Result;
      Result << std::move(IncomingRules);
      Result << std::move(OutcomingRules);
      return Result;
   }

TRules GenerateRules(const TProtocolsInfoTable &ProtocolsInfoTable, const TMetaRuleInfos &MetaRuleInfos)
   {
      TRules Result;

      for(const TMetaRuleInfo &MetaRuleInfo: MetaRuleInfos)
         {
            for(const QString &ProtocolName: MetaRuleInfo.ProtocolNames)
               {
                  ASSERT_X(ProtocolsInfoTable.contains(ProtocolName), "No such protocol name \"" << ProtocolName
                                                                      << "\" in ProtocolsInfoTable!");
                  TProtocolInfoPtr ProtocolInfoPtr = ProtocolsInfoTable.find(ProtocolName).value();
                  TRules RulesForProtocolName = GenerateRulesForProtocolName(*ProtocolInfoPtr, MetaRuleInfo);
                  Result << std::move(RulesForProtocolName);
               }
         }

      return Result;
   }

QDebug operator<<(QDebug Out, TDirection Direction)
   {
      typedef std::underlying_type<TDirection>::type TUT;
      static const TUT MAX = static_cast<TUT>(TDirection::LAST);
      static const std::array<const char *, MAX> Str = { { "Input", "Output" } };
      const TUT N = static_cast<TUT>(Direction);
      if(N > MAX)
         {
            Out << "UnknownDirection";
            return Out;
         }
      return Out << QString(Str[N]);

   }

QDebug operator<<(QDebug Out, TRule Rule)
   {
      Out << "TRule(";
      Out << "ProcessName:" << Rule.ProcessName;
      Out << ", UserName:" << Rule.UserName;
      Out << ", Host:" << Rule.Host;
      Out << ", Direction:" << Rule.Direction;
      Out << ", Ports:" << Rule.Ports;
      Out << ", PortType:" << Rule.PortType;
      Out << ", Actions:" << Rule.Actions;
      Out << ")\n";
      return Out;
   }
