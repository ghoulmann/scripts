#!/bin/bash

THIS_DIR=$(cd "$(dirname "$0")"; pwd)

if [ "$#" -ne 1 ]
then
   echo "Usage:"
   echo "   CheckDisksSMART.sh localhost"
   echo "   CheckDisksSMART.sh server.asdf.com"
   exit 1
fi

SERVER="$1"

STATS=`ssh $SERVER 'bash -s' < $THIS_DIR/GetDisksStats.sh`
#FAILED=`cat sample.txt | awk '
FAILED=`echo "$STATS" | awk '
   { 
      if($1 ~ /^========/) {
         DISK_IS_BEING_PROCESSED = $0
         OUTPUTED = 0
      }
      else if($NF > 0) {
         if(OUTPUTED == 0) {
            OUTPUTED = 1
            print DISK_IS_BEING_PROCESSED
         }
         print $0
      }
   }
'`

if [ -z "$FAILED" ]
then
   echo "All SMARTs good"
   echo "$STATS"
   exit
else
   echo "$STATS"
   exit 2
fi
