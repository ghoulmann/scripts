#/bin/bash

if [ "$#" -lt "1" ]
then
   echo "Usage:"
   echo "./LoggedExecuteOrWriteMeMessage.sh some_script.sh parameter1_for_your_script parameter2 and so on"
   exit
fi

SCRIPT_NAME="$1"
TYPESCRIPT_PATH="$THIS_DIR/$SCRIPT_NAME-typescript.txt"
LOG_PATH="$THIS_DIR/$SCRIPT_NAME.log"

echo "Started at `date`" >> $LOG_PATH
rm $TYPESCRIPT_PATH

cd $THIS_DIR
script -ec "$SCRIPT_NAME $2 $3 $4 $5 $6 $7 $8 $9" $TYPESCRIPT_PATH
EXIT_CODE=$?

echo "`locale`" >> $LOG_PATH

if [ "$EXIT_CODE" -eq "0" ]
then
   printf "Successfully finished at `date`, exitcode $EXIT_CODE\n\n" >> $LOG_PATH
   exit
fi

echo "subj." | mail -subject "Exit code of $SCRIPT_NAME is $EXIT_CODE" -A $TYPESCRIPT_PATH dimanne@ya.ru
echo "subj." | mail -subject "Exit code of $SCRIPT_NAME is $EXIT_CODE" dimanne@ya.ru
printf "NOT successfully finished at `date`, exitcode $EXIT_CODE\n\n" >> $LOG_PATH
