#include <string.h>
#include "inc\lwsc_alloc.h"

#define LWSC_HPT_LEN 0x400

lwsc_header *lwsc_hpt;
static lwsc_header *hp, *tp;
char lwsc_mem[LWSC_MEM_SZ];

lwsc_header *lwsc_header_get(short id) {
	for (tp = (lwsc_header *)lwsc_mem; tp->id != id; ++tp)
		if (tp->end)
			return LWSC_NULL;
	return tp;
}

short lwsc_calc(void) {
	short total;

	total = 0;
	tp = (lwsc_header *)lwsc_mem;

	do {
		if (tp->avl)
			continue;
		total += lwsc_sz(tp->lg_sz);
	} while (!(tp++)->end);
	return LWSC_MEM_SZ - LWSC_HPT_SZ - total;
}

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

void *lwsc_fetch(short id) {
	char *p;

	p = lwsc_mem + LWSC_HPT_SZ;

	for (tp = (lwsc_header *)lwsc_mem; tp->id != id; ++tp) {
		if (tp->end)
			return LWSC_NULL;
		p += lwsc_sz(tp->lg_sz);
	}

	if (tp->avl)
		return LWSC_NULL;
	return (void *)p;
}

void lwsc_delete(short id) {
	char *p;
	short sz;

	tp = lwsc_header_get(id);
	p = (char *)lwsc_fetch(id);
	sz = lwsc_sz(tp->lg_sz);

	if (tp->end && tp != lwsc_hpt)
		(tp - 1)->end = 1;

	memcpy(p, p + sz, lwsc_mem + LWSC_MEM_SZ - LWSC_HPT_SZ - p - sz);
	p = (char *)tp;
	if (hp != (lwsc_header *)lwsc_mem)
		--hp;
	memcpy(p, p + sizeof(lwsc_header), lwsc_mem + LWSC_HPT_SZ - p - sizeof(lwsc_header));
}

void lwsc_compact(void) {
	tp = (lwsc_header *)lwsc_mem;

	do {
		if (tp->avl)
			lwsc_delete(tp->id);
	} while (!(tp++)->end);
}

short lwsc_alloc(char lg_sz) {
	char h;

	if (!hp) {
		hp = lwsc_hpt = (lwsc_header *)lwsc_mem;
		hp->lg_sz = lg_sz;
		hp->end = 1;
		hp->id = 0;
		return (hp++)->id;
	}

	h = (lwsc_calc() >= lwsc_sz(lg_sz));

	if (hp - lwsc_hpt == LWSC_HPT_LEN) {
		hp = lwsc_hpt;
		do
			if (hp->avl && hp->lg_sz == lg_sz) {
				hp->end = 0;
				hp->avl = 0;
				hp->id = hp - lwsc_hpt;
				return hp->id;
			}
		while (!(hp++)->end);

		if (!(--hp)->avl && h) {
			lwsc_compact();
			return lwsc_alloc(lg_sz);
		}
	} else if (!h)
		return -1;
	hp->lg_sz = lg_sz;
	(hp - 1)->end = 0;
	hp->end = 1;
	hp->id = hp - lwsc_hpt;
	return (hp++)->id;
}

void lwsc_free(short id) {
	lwsc_header_get(id)->avl = 1;
}
