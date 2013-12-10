#!/bin/bash

set -e

function RunVerbosely() { echo "$@" ; "$@" ; }

function SerPerms
   {
      CHMOD_CMD="$1"
      CHOWN_CMD="$2"
      SOME_PATH="$3"
      PERMS="$4"
      OWNER="$5"

      if [ -z "$CHMOD_CMD" ]
      then
         echo "Empty chmod cmd"
         exit 1
      fi
      
      if [ -z "$CHOWN_CMD" ]
      then
         echo "Empty chown cmd"
         exit 2
      fi

      if [ -z "$SOME_PATH" ]
      then
         echo "Empty path"
         exit 3
      fi
      if [ -z "$PERMS" ]
      then
         echo "Empty permissions"
         exit 4
      fi
      
      RunVerbosely $CHMOD_CMD $PERMS $SOME_PATH

      if [ -n "$OWNER" ]
      then
         RunVerbosely $CHOWN_CMD $OWNER $SOME_PATH
      fi
   }

CHMOD_R="chmod -R"
CHOWN_R="chown -R"
SUDO_CHMOD_R="sudo chmod -R"
SUDO_CHOWN_R="sudo chown -R"
CHMOD="chmod"
CHOWN="chown"
SUDO_CHMOD="sudo chmod"
SUDO_CHOWN="sudo chown"

SerPerms "$CHMOD"		"$CHOWN"	/home/Void			700 dimanne:dimanne
SerPerms "$CHMOD"		"$CHOWN"	/home/Void/Yandex		700 dimanne:dimanne
SerPerms "$CHMOD"		"$CHOWN"	/home/Void/YandexDisk		700 dimanne:dimanne
SerPerms "$CHMOD"		"$CHOWN"	/home/Void/YandexDiskDecrypted	700 dimanne:dimanne
SerPerms "$CHMOD"		"$CHOWN"	/home/Void/pron			700 dimanne:dimanne
SerPerms "$CHMOD"		"$CHOWN"	/mnt/backup1			700 dimanne:dimanne

SerPerms "$SUDO_CHMOD_R"	"$SUDO_CHOWN_R"	/mnt/freedata/People		700 dimanne:dimanne
SerPerms "$CHMOD"		"$SUDO_CHOWN"	/mnt/freedata/People		750 dimanne:photos_watchers
SerPerms "$CHMOD_R"		"$SUDO_CHOWN_R"	/mnt/freedata/People/Photos	750 dimanne:photos_watchers

SerPerms "$SUDO_CHMOD"		"$SUDO_CHOWN"	/mnt/backup2			700 yulya:yulya
