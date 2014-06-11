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

USERNAME_LENTH="$((2 + $RANDOM % 9))" # [2; 2+8]
printf "Generating UserName ($USERNAME_LENTH chars length): "
GetRandomChars $USERNAME_LENTH

PASSWORD_LENGTH="$((12 + $RANDOM % 19))" # [12; 12+18]
printf "Generating Password ($PASSWORD_LENGTH chars length): "
GetRandomChars $PASSWORD_LENGTH

echo

