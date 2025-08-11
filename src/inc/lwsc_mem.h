#ifndef LWSC_MEM_H
#define LWSC_MEM_H

#define LWSC_NULL 		((void *)0)
#define LWSC_MEM_SZ 	0x1800 /* 6KB */
#define LWSC_PAGE_SZ 	0x0400 
#define LWSC_BUF_SZ 	0x0400 /* 1KB */
#define LWSC_HPT_SZ 	0x0400 /* 1KB */

extern char lwsc_mem[LWSC_MEM_SZ];

typedef struct {
	unsigned char lg_sz: 4, avl: 1, end: 1, resv: 2;
} lwsc_header;

extern lwsc_header *lwsc_hpt;

extern short lwsc_sz(char lg_sz);
extern char *lwsc_page_get(char n);
extern void lwsc_page_cls(char n);
extern void lwsc_compact(void);
extern short lwsc_calc(void);
extern short lwsc_alloc(char lg_sz);
extern short lwsc_realloc(short id, char lg_sz);
extern void *lwsc_fetch(short id);
extern void lwsc_delete(short id);
extern void lwsc_free(short id);

#endif
