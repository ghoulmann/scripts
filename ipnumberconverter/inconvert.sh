#!/bin/bash

# Usage wxamples
#./inconvert.sh i 16777343
#127.0.0.1
#./inconvert.sh i 127.0.0.1
#16777343

dec2ip () 
   {
      local ip dec=$@
      for e in {3..0}
      do
         ((octet = dec / (256 ** e) ))
         ((dec -= octet * 256 ** e))
         ip+=$delim$octet
         delim=.
      done
      printf '%s' "$ip"
   }
   
ip2dec () 
   {
      local a b c d ip=$@
      IFS=. read -r a b c d <<< "$ip"
      printf '%d\n' "$((a * 256 ** 3 + b * 256 ** 2 + c * 256 + d))"
   }
INVERTED_IP=""
invertip()
   {
      INVERTED_IP=`echo $@ | awk -F '.'  '{ for (i=NF; i>=1; i--) printf (i!=1) ? $i FS : $i "\n" }'`   
   }

ARG="$1"
   
if [[ "$1" == "i" ]]
then
   ARG="$2"
fi

if [[ $ARG == *.* ]]
then
   if [[ "$1" == "i" ]]
   then
      invertip $ARG
      ip2dec "$INVERTED_IP"
   else
      ip2dec $ARG
   fi   
else
   if [[ "$1" == "i" ]]
   then      
      invertip $(dec2ip $ARG)
      printf $INVERTED_IP
   else
      dec2ip $ARG
   fi   
   echo ""
fi
