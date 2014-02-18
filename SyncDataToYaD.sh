#/bin/bash

THIS_DIR=$(cd "$(dirname "$0")"; pwd)
source $THIS_DIR/SyncDataBase.inc

YA_PATH="/home/Void/YandexDisk"
YAD_PATH="/home/Void/YandexDiskDecrypted"
PRON_PATH="/mnt/media/VideoLibrary/!!!/!!!Enc"

set -e

RSYNC_OPTIONS="--size-only --recursive  --verbose --human-readable --progress --itemize-changes --stats"

DoRsync "/mnt/freedata/BestMusic/" "$YA_PATH/BestMusic/"

OLD_PRON_ARCH_NAME="enc_pron.old.tar.gz"
NEW_PRON_ARCH_NAME="enc_pron.new.tar.gz"
RunVerbosely rm -rf "$THIS_DIR/$NEW_PRON_ARCH_NAME"
RunVerbosely tar cvzf "$THIS_DIR/$NEW_PRON_ARCH_NAME" "/mnt/media/VideoLibrary/!!!/!!!Enc"
if [ -f "${YAD_PATH}/pron2/$NEW_PRON_ARCH_NAME" ]; then
   set +e
   RunVerbosely mv "${YAD_PATH}/pron2/$NEW_PRON_ARCH_NAME" "${YAD_PATH}/pron2/$OLD_PRON_ARCH_NAME"
   set -e
fi
DoRsync "$THIS_DIR/$NEW_PRON_ARCH_NAME" "${YAD_PATH}/pron2/"
RunVerbosely rm -rf "$THIS_DIR/$NEW_PRON_ARCH_NAME"


exit 0;

RunVerbosely sudo cp -r /etc/.git /home/Void/sys/etc
RunVerbosely sudo chown -R dimanne /home/Void/sys/etc
DoRsync /home/Void/sys/etc/ ${YAD_PATH}/etc/
RunVerbosely rm -rf /home/Void/sys/etc/.git
