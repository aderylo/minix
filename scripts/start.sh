#!bin/bash

cd ..
qemu-img create -f qcow2 -F raw -o backing_file=/home/students/inf/PUBLIC/SO/scenariusze/4/minix.img minix.img
qemu-system-x86_64 -curses -drive file=minix.img -enable-kvm -net user,hostfwd=tcp::10022-:22 -net nic,model=virtio -m 1024M
