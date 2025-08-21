#ifndef LWSC_IO_H
#define LWSC_IO_H

#define LWSC_PAGE_IN 	0
#define LWSC_PAGE_OUT 	1
#define LWSC_PAGE_LOG 	2
#define LWSC_IOBUF_SZ 	0x0C00
#define LWSC_PAGE_SZ 	0x0400

extern char *lwsc_page_get(char n);

#endif
