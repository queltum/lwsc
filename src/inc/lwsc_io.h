#ifndef LWSC_IO_H
#define LWSC_IO_H

#define LWSC_IOBUF_SZ 1024

extern char *lwsc_readin(void);
extern void lwsc_panic(char msg, char ctx, char *p, short where);

#endif