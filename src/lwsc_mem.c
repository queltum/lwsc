#include <string.h>

#include "inc\lwsc_mem.h"
#include "inc\lwsc_log.h"

lwsc_header *lwsc_hpt;
char lwsc_mem[LWSC_MEM_SZ];

static lwsc_header *hp;

short lwsc_sz(char lg_sz) {
	switch (lg_sz) {
		case 0: return 1;
		case 1: return 2;
		case 2: return 4;
		case 3: return 8;
		case 4: return 16;
		case 5: return 32;
		case 6: return 64;
		case 7: return 128;
		default: return 0;
	}
}

void lwsc_page_cls(char n) {
	memset(lwsc_mem + n * LWSC_PAGE_SZ, 0, LWSC_BUF_SZ);
}

short lwsc_calc(void) {
	short total;
	lwsc_header *tp;

	total = 0;
	tp = lwsc_hpt;

	do {
		if (tp->avl)
			continue;
		total += lwsc_sz(tp->lg_sz);
	} while (!(tp++)->end);
	return LWSC_MEM_SZ - total;
}

short lwsc_alloc(char lg_sz) {
	char h;

	if (!hp) {
		hp = lwsc_hpt = (lwsc_header *)(lwsc_mem + LWSC_BUF_SZ);
		hp->lg_sz = lg_sz;
		hp->end = 1;
		return hp++ - lwsc_hpt;
	}

	h = (lwsc_calc() >= lwsc_sz(lg_sz));

	if (hp - lwsc_hpt == LWSC_HPT_SZ - 1) {
		hp = lwsc_hpt;
		do
			if (hp->avl && hp->lg_sz == lg_sz) {
				hp->end = 0;
				hp->avl = 0;
				return hp - lwsc_hpt;
			}
		while (!(hp++)->end);

		if (!(--hp)->avl) {
			lwsc_panic(LWSC_MOD_MEM, LWSC_MSG_HPT_OVERFLOW);
			return -1;
		}

	} else if (!h) {
		lwsc_panic(LWSC_MOD_MEM, LWSC_MSG_NO_MEMORY);
		return -1;
	} else {
		hp->lg_sz = lg_sz;
		(hp - 1)->end = 0;
		hp->end = 1;
		return hp++ - lwsc_hpt;
	}
}

void lwsc_free(short id) {
	if (id < 0)
		return;
	lwsc_hpt[id].avl = 1;
}

void *lwsc_fetch(short id) {
	char *p;
	lwsc_header *tp;

	if (lwsc_hpt[id].avl) {
		lwsc_panic(LWSC_MOD_MEM, LWSC_MSG_UNAVALIABLE_HEADER);
		return LWSC_NULL;
	}

	for (tp = lwsc_hpt, p = lwsc_mem; tp != lwsc_hpt + id; ++tp)
		p += lwsc_sz(hp->lg_sz);
	return (void *)p;
}
