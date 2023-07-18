#!/bin/bash

# Usage: fix-format [-a]
#    -a  process all files (not just modified files)

GIT_LSFILES_FLAGS="-o -m"

while [[ $# -gt 0 ]]; do
	key="$1"
	case $key in
	-a|--all)
	    GIT_LSFILES_FLAGS=""
	    ;;
	esac
    shift # past argument
done

CFORMATTER=${CFORMATTER:-clang-format-11}

$CFORMATTER --version

DIRECTORIES_TO_CHECK="example"

list=$(
	(git ls-files $GIT_LSFILES_FLAGS -- $DIRECTORIES_TO_CHECK on ; \
	 git status --porcelain -- $DIRECTORIES_TO_CHECK 2>/dev/null \
	 | grep -E '^A' \
	 | sed -e "s,^A,,") \
	| grep -E '\.cc$|\.h$'
)

declare -i TOTAL_NUM_LINES=0
while read path; do
    if [ -f "$path" ] ; then
        echo "$path"
        $CFORMATTER -style=file "$path" > /tmp/clang.format.log
        NUM_LINES=$(diff $path /tmp/clang.format.log | wc -l)
        if [ $NUM_LINES -gt 0 ] ; then
            echo "Number of changed lines : $NUM_LINES"
            echo $(diff $path /tmp/clang.format.log)
        fi
        TOTAL_NUM_LINES=$((TOTAL_NUM_LINES + NUM_LINES))
        $CFORMATTER -style=file -i "$path"
    fi
done <<< "$list"
if [ $TOTAL_NUM_LINES -gt 0 ] ; then
    exit 1
fi
exit 0
