#!/bin/bash
CURRENT=$(cd `dirname $0`; pwd)
SUPERVISE=${CURRENT}/supervise
status_dir="${CURRENT}/status"
[[ ! -d $status_dir ]] && mkdir -p $status_dir

echo -n -e "start qt LCD display process!\n"
mkdir -p $status_dir/start

cmd="${CURRENT}/aladdin_client"
${CURRENT}/supervise -p "$status_dir/start" -f "$cmd"
