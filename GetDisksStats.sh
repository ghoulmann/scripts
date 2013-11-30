#!/bin/bash

for i in `ls /dev/sd* | egrep "/dev/sd.$"`
do
   echo "================ $i ================"
   sudo smartctl -A $i | grep  -E "^ *5 "\|"^ *10 "\|"^ *196 "\|"^ *197 "\|"^ *198 "
   echo; echo;
done
