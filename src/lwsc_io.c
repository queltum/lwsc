#include <stdio.h>

#include "inc\lwsc_io.h"

static char lwsc_iobuf[LWSC_IOBUF_SZ];

const char *lwsc_readin(void) {
	return fgets(lwsc_iobuf, LWSC_IOBUF_SZ, stdin);
}

