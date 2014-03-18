#!/bin/sh -e

usage() {
    cat <<EOF
Simple gnuplot wrapper for plotting data from files
USAGE: chart [-t TERMINAL] [-o OUTPUT] FILE:X_COL:Y_COL ...
EOF
    exit 1;
}

if [ -z "$*" ]; then usage; fi

TERMINAL=
OUTPUT=
EXTRA=
while [ -n "$1" ] && echo $1 | grep '^-' >/dev/null 2>&1; do
    case $1 in
        -t) TERMINAL=$2; shift ;;
        -o) OUTPUT=$2; shift ;;
        -e) EXTRA=$2; shift ;;
        --help) usage; ;;
    esac
    shift
done

finish() { rm -f tmp.gp; }
trap 'finish' INT
(
    if [ -n "$TERMINAL" ]; then echo "set terminal $TERMINAL"; fi
    if [ -n "$OUTPUT" ]; then echo "set output \"$OUTPUT\""; fi
    if [ -n "$EXTRA" ]; then echo "$EXTRA"; fi
    FIRST=y
    for ARG in "$@"; do
        if echo "$ARG" | grep : >/dev/null 2>&1; then
            FILE=`echo "$ARG" | perl -nle 'print $1 if /([^:]*)/'`
            USING=`echo "$ARG" | perl -nle 'print $1 if /[^:]*:(.*)/'`
        else
            FILE=$ARG
            USING=1:2
        fi
        if [ -n "$FIRST" ]; then FIRST=; printf "plot "; else printf ", "; fi
        printf "\"$FILE\" using $USING with lines title \"$FILE\""
    done
    echo
    if [ -z "$TERMINAL" ]; then echo "pause -1"; fi
) > tmp.gp && gnuplot tmp.gp || true
finish
