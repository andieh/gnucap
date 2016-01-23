#!/bin/sh

set -e
set -x
GNUCAP=${GNUCAP-gnucap}

# check if it's there
which gnucap | grep src/gnucap

# check whether it runs
echo end | $GNUCAP | grep "ABSOLUTELY NO WARRANTY"

# gnucap doesn't know foo
echo foo | $GNUCAP | grep "what's this"