#!/bin/bash

#VideoLibrary            disk                  rsync --times --recursive          --verbose --human-readable --progress --itemize-changes --stats /mnt/freedata/home/Void/samba/194.85.80.88/video/top/imdb\ top\ 250/ /media/disk/VideoLibrary/\!imdb\ top\ 250/

RAID_PATH="/mnt/media"
FREEDATA_PATH="/mnt/freedata"
MYHOME_PATH="/home/Void"

#--checksum - even if time of dst does not coincide with time of src it DOES NOT copy if files are equal
# without this iption if time of dst does not coincide with time of src rsync will perform transfer
RSYNC_OPTIONS="--times --recursive          --verbose --human-readable --progress --itemize-changes --stats"

function DoRsync
   {    
      echo; echo; echo; echo;
      echo "RSYNC $1   ======>   $2"
      echo; 
      rsync ${RSYNC_OPTIONS} $1 $2
      echo "========================================================================================";
   
   }

function DoRsyncDelete
   {    
      echo; echo; echo; echo;
      echo "RSYNC $1   ======>   $2"
      echo; 
      rsync ${RSYNC_OPTIONS} --delete $1 $2
      echo "========================================================================================";
   
   }


set -e

# ===================================================================================================================
# =================================================== home & ssd ====================================================
# ===================================================================================================================
DoRsync ${MYHOME_PATH}/devel/ ${FREEDATA_PATH}/home/Void/devel/
DoRsync ${MYHOME_PATH}/Yandex/ ${FREEDATA_PATH}/home/Void/Yandex/


# ===================================================================================================================
# ==================================================== freedata =====================================================
# ===================================================================================================================
DoRsync ${FREEDATA_PATH}/People/             /mnt/backup1/People/             # People                   => backup1
DoRsync ${FREEDATA_PATH}/BestMusic/          /mnt/backup1/BestMusic/          # BestMusic                => backup1
DoRsync ${FREEDATA_PATH}/MyScience/          /mnt/backup1/MyScience/          # MyScience freedata       => backup1
DoRsync ${FREEDATA_PATH}/Funny\&Interesting/ /mnt/backup1/Funny\&Interesting/ # Funny & Interesting disk => backup1

# ===================================================================================================================
# ===================================================== media =======================================================
# ===================================================================================================================
# Important part of video library   disk => backup1
DoRsync ${RAID_PATH}/VideoLibrary/\!\!\!/             /mnt/backup1/VideoLibrary/\!\!\!/
DoRsync ${RAID_PATH}/VideoLibrary/\!EducationalFilms/ /mnt/backup1/VideoLibrary/\!EducationalFilms/



#-r, --recursive
#              This tells rsync to  copy  directories  recursively.
#
#-a, --archive
#              This  is equivalent to -rlptgoD. It is a quick way of saying you
#              want recursion and want to preserve almost everything  (with  -H
#              being  a  notable  omission).
#
#-v, --verbose
#              This option increases the amount of information  you  are  given
#              during the transfer.
#
#-z, --compress
#              With  this  option, rsync compresses the file data as it is sent
#              to the destination machine, which reduces  the  amount  of  data
#              being  transmitted  -- something that is useful over a slow con-
#              nection.
#
#-u, --update
#              This  forces rsync to skip any files which exist on the destina-
#              tion and have a modified time that  is  newer  than  the  source
#              file.   (If an existing destination file has a modification time
#              equal to the source file's, it will be updated if the sizes  are
#              different.)
#-o, --owner
#              This  option  causes  rsync  to set the owner of the destination
#              file to be the same as the source file, but only if the  receiv-
#              ing  rsync  is being run as the super-user
#
#-p, --perms
#              This option causes the receiving rsync to  set  the  destination
#              permissions to be the same as the source permissions.  (See also
#              the --chmod option for a way to modify what rsync  considers  to
#              be the source permissions.)
#
#--delete
#              This  tells  rsync to delete extraneous files from the receiving
#              side (ones that aren't on the sending side), but  only  for  the
#              directories  that  are  being synchronized.  You must have asked
#              rsync to send the whole directory (e.g. "dir" or "dir/") without
#              using  a  wildcard  for  the directory's contents (e.g. "dir/*")
#              since the wildcard is expanded by the shell and rsync thus  gets
#              a  request  to  transfer individual files, not the files' parent
#              directory.  Files that are excluded from the transfer  are  also
#              excluded from being deleted unless you use the --delete-excluded
#              option or mark the rules as only matching on  the  sending  side
#              (see the include/exclude modifiers in the FILTER RULES section).
#
#
