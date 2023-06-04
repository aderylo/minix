#!bin/bash

cd /
patch -p1 < ab123456.patch

cd /usr/src/minix/fs/procfs 
make && make install
echo "procfs done!" 

cd  /usr/src/minix/servers/pm
make && make install 
echo "pm done!" 

cd /usr/src/minix/drivers/storage/ramdisk
make && make install 
echo "ramdisk done!"

cd /usr/src/minix/drivers/storage/memory
make && make install 
echo "memory done!"

cd /usr/src/lib/libc
make && make install 
echo "libc done!" 

cd /usr/src/releasetools
make do-hdboot
echo "releasetools done!"

reboot
