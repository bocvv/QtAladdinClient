#!/bin/bash
### BEGIN INIT INFO
# Provides: lsb-ourdb
# Required-Start: $local_fs remote_fs
# Required-Stop: $local_fs $remote_fs
# Default-Start:  2 3 4 5
# Default-Stop: 0 1 6
# Short-Description: start and stop OurDB
# Description: OurDB is a very fast and reliable database
#    engine used for illustrating init scripts
### END INIT INFO

cd /root/wangbw/work/aladdin_client
source /etc/profile
bash /root/wangbw/work/aladdin_client/start.sh

sleep 6s
kill -9 $(pidof aladdin_client)
