#!bin/bash

cd /
patch -p1 < ab123456.patch

cd  /usr/src/minix/servers/sched
make && make install 
echo "sched done!" 

cd  /usr/src/minix/servers/pm
make && make install 
echo "pm done!"

cd /usr/src/lib/libc
make && make install 
echo "libc done!" 

cd /usr/src/releasetools
make do-hdboot
echo "releasetools done!"

reboot
