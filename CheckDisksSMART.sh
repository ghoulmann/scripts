#/bin/bash
THIS_DIR=$(cd "$(dirname "$0")"; pwd)
$THIS_DIR/LoggedExecuteOrWriteMeMessage.sh $THIS_DIR/CheckDisksSMART_impl.sh $1
