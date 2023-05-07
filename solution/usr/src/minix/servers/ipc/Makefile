# Makefile for IPC server
PROG=	ipc
SRCS=	main.c utility.c shm.c sem.c do_printmessage.c

DPADD+=	${LIBSYS}
LDADD+=	-lsys

FILES=ipc.conf
FILESNAME=ipc
FILESDIR= /etc/system.conf.d

.include <minix.service.mk>
