#!/bin/bash

#rm out.sorted
#while read line
#do
#   FIRST_COLUMNS=`echo $line | cut -d ' ' -f 1,2,3`
#   #echo $FIRST_COLUMNS
   
#   SECOND_COLUMNS=`echo $line | cut -d ' ' -f 4,5,6,7`
#   #echo "Second columns $SECOND_COLUMNS"
#   SORTED=`echo $SECOND_COLUMNS | xargs -n1 | sort -r -g | xargs`
#   #echo "Sorted $SORTED"
#   
#   echo "$FIRST_COLUMNS $SORTED"
#done <out.txt >out.sorted

./chart.sh -t png -e "set terminal png size 3600,500" -o results/ip.png out.txt:1:2
./chart.sh -t png -e "set terminal png size 3600,500" -o results/hosts.png out.txt:1:3
./chart.sh -t png -e "set terminal png size 3600,500" -o results/vsz_rss.png out.txt:1:{4..5}
