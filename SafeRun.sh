#/bin/bash

if [ "$#" -lt 1 ]
then
   echo "Usage:"
   echo "   SafeRun.sh /path/to/programme option1 option2"
   exit 1
fi

PROGRAMME="$@"

strace -e trace=desc "$PROGRAMME" 2>&1 | awk '
BEGIN {
   n = 0;
   N = 10;
}
{
   if(n == N)
      n = 0;
   HISTORY[n]=$0;
   # print n, HISTORY[n];
   ++n;
   if($0 ~ /\/home\/Void|\/mnt/) {
      for(i = n; i < N; ++i)
         { print "    ", i, HISTORY[i]; }
      for(i = 0; i < n; ++i)
         { print "    ", i, HISTORY[i]; }
      exit;
   }
}'
