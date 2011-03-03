#!/bin/sh
HOOKWRITE_UPDATE_FILE=$HOME/tmp/cat \
HOOKWRITE_COMMAND='echo hoge' \
LD_PRELOAD=/usr/local/lib/libhookwrite.so \
  /bin/cat $@
