#include <stdio.h>
#include <stdlib.h>

#include "inc\lwsc_alloc.h"

void lwsc_mem_dump(void);
void lwsc_hpt_dump(void);

int main(void) {
	return 0;
}

void lwsc_hpt_dump(void) {
	short i;
	lwsc_header *hp;

	hp = (lwsc_header *)lwsc_mem;

	do {
		printf("id:%d, sz: %d, end: %d, avl: %d\n", hp->id, 
			lwsc_sz(hp->lg_sz), (hp->end)? 1 : 0, (hp->avl)? 1 : 0);
	} while (!(hp++)->end);

	// for (i = 0; i < 1024; ++i) {
	// 	printf("id:%d, sz: %d, end: %d, avl: %d\n", hp->id, 
	// 		lwsc_sz(hp->lg_sz), (hp->end)? 1 : 0, (hp->avl)? 1 : 0);
	// 	++hp;
	// }
}

void lwsc_mem_dump(void) {
	short i, j;
	char *p;

	p = lwsc_mem + LWSC_HPT_SZ;

	for (i = 0; i < 40; ++i, ++p) {
		if (!(i % 8))
			putchar('\n');
		printf("%0.2x ", *p);
	}
}