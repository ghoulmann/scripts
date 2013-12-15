#/bin/bash

source SyncDataBase.inc

YAD_PATH="/home/Void/YandexDiskDecrypted"
PRON_PATH="/mnt/media/VideoLibrary/!!!/!!!Enc"

set -e

RSYNC_OPTIONS="--size-only --recursive  --verbose --human-readable --progress --itemize-changes --stats"

DoRsync "/mnt/media/VideoLibrary/!!!/!!!Enc/" ${YAD_PATH}/pron/

RunVerbosely sudo cp -r /etc/.git /home/Void/sys/etc
RunVerbosely sudo chown -R dimanne /home/Void/sys/etc
DoRsync /home/Void/sys/etc/ ${YAD_PATH}/etc/
RunVerbosely rm -rf /home/Void/sys/etc/.git
