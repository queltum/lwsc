#ifndef LWSC_ALLOC_H
#define LWSC_ALLOC_H

#define LWSC_NULL ((void *)0)
#define LWSC_MEM_SZ 0x3000
#define LWSC_HPT_SZ 0x0800

typedef struct {
	unsigned short id: 10, lg_sz: 3, avl: 1, end: 1, resv: 1;
} lwsc_header;

extern char lwsc_mem[LWSC_MEM_SZ];
extern lwsc_header *lwsc_header_get(short id);

extern short lwsc_sz(char lg_sz);
extern short lwsc_calc(void);
extern void *lwsc_fetch(short id);
extern void lwsc_delete(short id);
extern void lwsc_compact(void);
extern short lwsc_alloc(char lg_sz);
extern short lwsc_realloc(short id, char lg_sz);
extern void lwsc_free(short id);

#endif
