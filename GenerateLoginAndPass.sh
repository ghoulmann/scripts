#!/bin/bash

function GetRandomChars() {
   local LENGTH="$1"

   cat /dev/random | awk -v Length="$LENGTH" '
      BEGIN {       
         N = 0;
         RS="[0-9a-zA-Z]";
         FS="[0-9a-zA-Z]"
      }
      { 
         printf RT;
         if(++N == Length) {
            printf "\n";
            exit;
         }
      }
   '
}

echo

printf "UserName: "
GetRandomChars 6

printf "Password: "
GetRandomChars 30

echo

