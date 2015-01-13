#!/bin/bash

#VideoLibrary            disk                  rsync --times --recursive          --verbose --human-readable --progress --itemize-changes --stats /mnt/freedata/home/Void/samba/194.85.80.88/video/top/imdb\ top\ 250/ /media/disk/VideoLibrary/\!imdb\ top\ 250/

THIS_DIR=$(cd "$(dirname "$0")"; pwd)
source $THIS_DIR/SyncDataBase.inc

RAID_PATH="/mnt/media"
FREEDATA_PATH="/mnt/freedata"
MYHOME_PATH="/home/Void"

set -e

# ===================================================================================================================
# =================================================== home & ssd ====================================================
# ===================================================================================================================
DoRsync ${MYHOME_PATH}/devel/ ${FREEDATA_PATH}/home/Void/devel/
set +e # Due to root-owned certs/ directory we disable "exit on error" behaviour here
DoRsyncDelete ${MYHOME_PATH}/Yandex/ ${FREEDATA_PATH}/home/Void/Yandex/
set -e


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
#DoRsyncDelete ${RAID_PATH}/VideoLibrary/\!\!\!/             /mnt/backup1/VideoLibrary/\!\!\!/
DoRsync ${RAID_PATH}/VideoLibrary/\!\!\!/             /mnt/backup1/VideoLibrary/\!\!\!/
DoRsync ${RAID_PATH}/VideoLibrary/\!EducationalFilms/ /mnt/backup1/VideoLibrary/\!EducationalFilms/
