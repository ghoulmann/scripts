#!/bin/bash

# Need to escape "
#            and $
#            and \

#===================================================================================================================================================

COLOURIZED_PROMPT=$( cat <<THIS_IS_END_OF_HEREDOC
# Colorized prompt
if [ \$UID != 0  ] ; then
        PS1=\"\[\e[32;1m\]\u@\[\e[31;1m\]\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\\\\\\\\$ \"
else
        PS1=\"\[\e[31;1m\]\u@\[\e[31;1m\]\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\\\\\\\\$ \"
fi
THIS_IS_END_OF_HEREDOC
)

#===================================================================================================================================================

COLOURIZED_GREP=$( cat <<THIS_IS_END_OF_HEREDOC
# Colorized grep
export GREP_OPTIONS=\"--color=auto\"
export GREP_COLOR=\"1;32\"
THIS_IS_END_OF_HEREDOC
)


#===================================================================================================================================================

COMMON_SYS_ALIASES=$( cat <<THIS_IS_END_OF_HEREDOC
THIS_IS_END_OF_HEREDOC
)

#===================================================================================================================================================

COMMON_OTHER_ALIASES=$( cat <<"THIS_IS_END_OF_HEREDOC"
# ==================================== COMMON_OTHER_ALIASES ====================================
alias inc='$MYDEVEL/sys/ipnumberconverter/inconvert.sh'
alias histogram='sort | uniq -c | sort -rn | head -40 | awk '\"'\"'!max{max=\$1;}{r=\"\";i=s=60*\$1/max;while(i-->0)r=r\"#\";printf \"%15s %5d %s %s\",\$2,\$1,r,\"\n\";}'\"'\"''
alias numstat='sort -n | awk '\"'\"'{ sum+=\$1; sumsq+=\$1*\$1; count[NR] = \$1; } END { print \"Min: \" count[1]; print \"Max: \" count[NR];  print \"Average: \"sum/NR; printf \"Median: \"; if (NR % 2) { print count[(NR + 1) / 2]; } else { print (count[(NR / 2)] + count[(NR / 2) + 1]) / 2.0; } print \"StdDev: \" sqrt(sumsq/NR - (sum/NR)**2); }'\"'\"''

THIS_IS_END_OF_HEREDOC
)

#===================================================================================================================================================


COMMON_GIT_ALIASES=$( cat <<"THIS_IS_END_OF_HEREDOC"
# ==================================== COMMON_GIT_ALIASES ====================================
alias  gs='echo \"git status\"; git status'
alias  gc='echo \"git checkout\"; git checkout'
alias  gb='echo \"git branch\"; git branch'

alias  gca='echo \"git commit --amend\"; git commit --amend'
alias  gco='echo \"git commit\"; git commit'

alias  gsr='echo \"git svn find-rev\"; git svn find-rev'
alias  gsu='echo \"git svn rebase\"; git svn rebase'
alias  gsc='echo \"git svn dcommit\"; git svn dcommit'

alias  gcp='echo \"git cherry-pick\"; git cherry-pick'

alias mycommits='echo \"\"; git log --author dimanne'


THIS_IS_END_OF_HEREDOC
)


#===================================================================================================================================================

IMPEDANCE_ALIASES=$( cat <<"THIS_IS_END_OF_HEREDOC"
# ==================================== IMPEDANCE_ALIASES ====================================
alias cdem='cd $MYDEVEL/EventManager_master/'

alias umountpr='fusermount -u /home/Void/pr_dec'
alias mountpr='encfs /mnt/media/VideoLibrary/\!\!\!/\!\!\!Enc/ /home/Void/pr_dec'

alias umountya='sudo umount /home/Void/YandexDisk'
alias  mountya='sudo mount -t davfs -o uid=dimanne https://webdav.yandex.ru /home/Void/YandexDisk'

alias umountyad='fusermount -u /home/Void/YandexDiskDecrypted'
alias  mountyad='encfs /home/Void/YandexDisk/something_interesting_here/ /home/Void/YandexDiskDecrypted'

alias incochrome='chromium-browser --user-data-dir=~/.config/chromium2 --incognito --proxy-server=\"socks5://localhost:9050\"'

alias SafeRun='/home/Void/sys/SafeRun.sh'

THIS_IS_END_OF_HEREDOC
)

#===================================================================================================================================================


SYS_MANAGEMENT=$( cat <<"THIS_IS_END_OF_HEREDOC"
# ==================================== SYS_MANAGEMENT ====================================
alias ports='sudo netstat -lptu'
alias sysupgrade='sudo aptitude update; sudo aptitude full-upgrade'


THIS_IS_END_OF_HEREDOC
)



#===================================================================================================================================================


YA_NOTE_SPIDERLOOKUPS=$( cat <<"THIS_IS_END_OF_HEREDOC"
# ==================================== YA SPIDERLOOKUPs ====================================
alias devzoraspiderlookup='ssh loon ssh dev-zora-00 spiderlookup'
alias devspiderspiderlookup='ssh loon ssh dev-spider-ru-00 spiderlookup'
alias zoraspiderlookup='ssh loon ssh zora2-00 spiderlookup'
alias piderspiderlookup='ssh loon ssh spider-ru-00 spiderlookup'

THIS_IS_END_OF_HEREDOC
)

YA_LOON_SPIDERLOOKUPS=$( cat <<"THIS_IS_END_OF_HEREDOC"
# ==================================== YA SPIDERLOOKUPs ====================================
alias devzoraspiderlookup='ssh dev-zora-00 spiderlookup'
alias devspiderspiderlookup='ssh dev-spider-ru-00 spiderlookup'
alias zoraspiderlookup='ssh zora2-00 spiderlookup'
alias piderspiderlookup='ssh spider-ru-00 spiderlookup'

THIS_IS_END_OF_HEREDOC
)

#===================================================================================================================================================


YA_LOON_BINARIES=$( cat <<"THIS_IS_END_OF_HEREDOC"
# ==================================== YA LOON BINARIES ====================================
alias loonfeed='ssh loon.search.yandex.net /home/dimanne/devel/build-kiwi/yweb/robot/kiwi/kwfeed/kwfeed'

THIS_IS_END_OF_HEREDOC
)


#===================================================================================================================================================

YA_RUN_BINARIES=$( cat <<"THIS_IS_END_OF_HEREDOC"
# ==================================== YA ====================================

# ================ spider related ================
alias         runfut='$YADEVEL/build-fut/yweb/robot/fut/fut'
alias runlogsubs_fut='$YADEVEL/build-fut/yweb/robot/fut/fut -h $YADEVEL/env-spider subs -c $YADEVEL/env-spider/config/logsubs.conf.xml -Le'
alias      runspider='$YADEVEL/build-spider/yweb/robot/spider/main/spider  -C $YADEVEL/env-spider/config/config.spider -e true'
alias        runzora='$YADEVEL/build-zora/yweb/robot/zora/zora -c $YADEVEL/env-zora/config/config.zora -le'
alias      runzoracl='$YADEVEL/build-zoracl/yweb/robot/zoracl/main/zoracl fetch --source=any --server=127.0.0.1 -i '
alias     barezoracl='$YADEVEL/build-zoracl/yweb/robot/zoracl/main/zoracl'
alias runlogicaldocs='$YADEVEL/build-logicaldocs/yweb/robot/logicaldocs/service/logicaldocs -C $YADEVEL/env-spider/config/config.logicaldocs -e true'
alias         deploy='$YADEVEL/arc-from-346k/yweb/robot/spider/scripts/deploy.sh'

alias            runyt='cd $YADEVEL/build-yt/bin/ && ./ytserver  --master --config $YADEVEL/env-yt/master_config.yson'
alias runytmsgbusproxy='cd $YADEVEL/build-yt/bin/ && ./messagebus_server  --config $YADEVEL/env-yt/proxy_config.yson'

alias  spiderlookup='$YADEVEL/arc-from-346k/packages/debian/spider/yandex-search-spider-common/Berkanavt/spider/scripts/spiderlookup'
alias spiderlookup2='$YADEVEL/arc-from-346k-2/packages/debian/spider/yandex-search-spider-common/Berkanavt/spider/scripts/spiderlookup'
alias            yr='$YADEVEL/arc-from-346k/yweb/scripts/yr'
alias           yr2='$YADEVEL/arc-from-346k-2/yweb/scripts/yr'
alias            ez='$YADEVEL/scripts/ExecuteOnAllZoras.sh'
alias            es='$YADEVEL/scripts/ExecuteOnAllSpiders.sh'

alias  downloadsbresources='$YADEVEL/arc-from-346k/yweb/robot/spider/scripts/DownloadSBResources.sh'
alias downloadsbresources2='$YADEVEL/arc-from-346k-2/yweb/robot/spider/scripts/DownloadSBResources.sh'


# ================ kiwi related ================
alias      rungene='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwgene         && ./kwgene -L --home=$YADEVEL/kiwi-home/ -d tuple  --dqaddr=224.0.0.1'
alias     baregene='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwgene         && ./kwgene'
alias      runmeta='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwmeta         && ./kwmeta -L --home=$YADEVEL/kiwi-home/ --server-host=localhost --fqdn=localhost'
alias     baremeta='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwmeta         && ./kwmeta'
alias      runnest='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwnest         && ./kwnest -L --home=$YADEVEL/kiwi-home/ --domain=tuple --segments-num 2 --dqaddr=224.0.0.1'
alias     barenest='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwnest         && ./kwnest'
alias       runhen='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwhen          && ./kwhen  -L --home=$YADEVEL/kiwi-home/ -d tuple --dqaddr=224.0.0.1 -s 31409'
alias      barehen='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwhen          && ./kwhen'
alias   runtracker='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwtracker/     && ./kwtracker'
alias    runloader='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwloader/      && ./kwloader --home=$YADEVEL/kiwi-home/ -l --announce=http://localhost'
alias   bareloader='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwloader/      && ./kwloader'
alias baremetaquery='$YADEVEL/arc-from-346k/yweb/robot/kiwi/scripts/metaquery.sh -F $YADEVEL/build-kiwi/yweb/robot/kiwi/kwfeed/kwfeed'
alias   runkwcalc='cd $YADEVEL/build-kiwi/yweb/robot/kiwi/kwcalc/server/ && ./kwcalc   --home=$YADEVEL/kiwi-home/udfs --verbose-main -w  $YADEVEL/build-kiwi/yweb/robot/kiwi/kwcalc/worker/kwcalcworker -j2'
alias runkwcalc_metastub='$YADEVEL/build-kiwi/yweb/robot/kiwi/kwcalc/server/kwcalc -H $YADEVEL/env-kwcalc/  -Ll -w  $YADEVEL/build-kiwi/yweb/robot/kiwi/kwcalc/worker/kwcalcworker -t 0 --meta-stub-file $YADEVEL/env-kwcalc/metadata.pb.txt -j 2 --restart-task-cnt 100'
alias      runfeed='$YADEVEL/build-kiwi/yweb/robot/kiwi/kwfeed/kwfeed'
alias feedmetadata='$YADEVEL/build-kiwi/yweb/robot/kiwi/kwfeed/kwfeed -d tuple -c  localhost gene -k egg -t write < $YADEVEL/env-kiwi/egg.pb.txt; $YADEVEL/build-kiwi/yweb/robot/kiwi/kwfeed/kwfeed -d tuple -c localhost  gene -k points -t write < $YADEVEL/env-kiwi/points.pb.txt; $YADEVEL/build-kiwi/yweb/robot/kiwi/kwfeed/kwfeed -d tuple -c localhost  gene  -k triggers write -t <  $YADEVEL/env-kiwi/triggers.pb.txt'
alias rundeployenable='ls -1 | xargs -I {} $YADEVEL/arc-from-346k/yweb/robot/kiwi/scripts/metaquery.sh -F $YADEVEL/build-kiwi/yweb/robot/kiwi/kwfeed/kwfeed -c localhost -f {}/deploy.mq:{}/enable.mq'

THIS_IS_END_OF_HEREDOC
)

#===================================================================================================================================================

YA=$( cat <<"THIS_IS_END_OF_HEREDOC"
# ==================================== YA ====================================

alias            ek='$YADEVEL/scripts/ExecuteOnAllKiwis.sh'

# ================ common ================

alias  prep='rm $YADEVEL/arc-from-346k/CMakeLists.txt.user;   echo \"ENABLE(NOLINK)\" >> $YADEVEL/arc-from-346k/local.cmake'
alias prep2='rm $YADEVEL/arc-from-346k-2/CMakeLists.txt.user; echo \"ENABLE(NOLINK)\" >> $YADEVEL/arc-from-346k-2/local.cmake'
alias sbrsync='$YADEVEL/scripts/sandbox_rsync.py'

THIS_IS_END_OF_HEREDOC
)

#===================================================================================================================================================



THIS_SCRIPT="$(basename "$0")"

function Usage() {
   echo "Usage:"
   echo "   $THIS_SCRIPT loon"
   echo "   $THIS_SCRIPT ya"
   echo "   $THIS_SCRIPT impedance"
   echo "   $THIS_SCRIPT server"
}




if [ "$1" = "loon" ]
then
   YADEVEL="/home/dimanne/devel"
   MYDEVEL="/home/dimanne/mydevel"   
   eval "echo \"$COLOURIZED_PROMPT\""
   eval "echo \"$COLOURIZED_GREP\""   
   eval "echo \"$COMMON_OTHER_ALIASES\""
   eval "echo \"$COMMON_GIT_ALIASES\""
   eval "echo \"$YA_RUN_BINARIES\""
   eval "echo \"$YA_LOON_SPIDERLOOKUPS\""



elif [ "$1" = "ya" ]
then
   YADEVEL="/home/Void/devel"
   MYDEVEL="/home/Void/mydevel"
   eval "echo \"$COMMON_OTHER_ALIASES\""
   eval "echo \"$COMMON_GIT_ALIASES\""
   eval "echo \"$SYS_MANAGEMENT\""
   eval "echo \"$YA_RUN_BINARIES\""
   eval "echo \"$YA\""
   eval "echo \"$YA_NOTE_SPIDERLOOKUPS\""
   eval "echo \"$YA_LOON_BINARIES\""



elif [ "$1" = "impedance" ]
then
   YADEVEL="/home/Void/Yandex/devel"
   MYDEVEL="/home/Void/devel"
   eval "echo \"$COMMON_OTHER_ALIASES\""
   eval "echo \"$COMMON_GIT_ALIASES\""
   eval "echo \"$SYS_MANAGEMENT\""
   eval "echo \"$YA_RUN_BINARIES\""
   eval "echo \"$YA\""
   eval "echo \"$IMPEDANCE_ALIASES\""
   eval "echo \"$YA_NOTE_SPIDERLOOKUPS\""
   eval "echo \"$YA_LOON_BINARIES\""



elif [ "$1" = "server" ]
then
   eval "echo \"$COMMON_OTHER_ALIASES\""
   eval "echo \"$COMMON_GIT_ALIASES\""
   eval "echo \"$SYS_MANAGEMENT\""
else
   Usage
   exit 1
fi

