#include <stdio.h>

#include "inc\lwsc_mem.h"
#include "inc\lwsc_log.h"

void lwsc_hpt_dump(void);

int main(void) {
	short i;

	for (i = 0; i < LWSC_HPT_SZ; ++i)
		lwsc_alloc(2);
	lwsc_hpt_dump();
	printf("%d\n", lwsc_calc());
	lwsc_alloc(2);
	printf("%s\n", lwsc_log_get());
	lwsc_free(0);
	lwsc_page_cls(0);
	printf("%d ?%s\n", lwsc_alloc(2), lwsc_log_get());
	lwsc_hpt_dump();
	return 0;
}

void lwsc_hpt_dump(void) {
	lwsc_header *hp;

	hp = lwsc_hpt;
	do {
		printf("id:%d, sz: %d, end: %d, avl: %d\n", hp - lwsc_hpt, 
			lwsc_sz(hp->lg_sz), (hp->end)? 1 : 0, (hp->avl)? 1 : 0);
	} while (!(hp++)->end);
}