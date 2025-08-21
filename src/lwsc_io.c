#include "inc\lwsc_io.h"

static char lwsc_iobuf[LWSC_IOBUF_SZ];

char *lwsc_page_get(char n) {
	return lwsc_iobuf + LWSC_PAGE_SZ * n;
}