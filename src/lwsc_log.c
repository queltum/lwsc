#include <stdio.h>
#include <string.h>

#include "inc\lwsc_log.h"

struct LWSCStatus lwsc_status;
static char *lwsc_log_level[LWSC_LOG_LEVEL_COUNT] = { "log", "warn", "error" };

void lwsc_status_update(char *p, short where, 
	lwsc_msg_id msg, lwsc_ctx_id ctx) {
	lwsc_status.p = p;
	lwsc_status.where = where;
	lwsc_status.msg = msg;
	lwsc_status.ctx = ctx;
}

void lwsc_log(lwsc_log_level lvl) {
	if (lwsc_status.where < 0 || lwsc_status.where >= LWSC_LOG_BUF_SZ)
		lwsc_status.where = 0;
	char buf[lwsc_status.where + 2];
	
	memset(buf, ' ', lwsc_status.where);
	buf[lwsc_status.where] = '^';
	buf[lwsc_status.where + 1] = '\0';

	fprintf(stdout, 
		"\n$lwsc-%s %s: %s at\n> %s  %s", 
		lwsc_log_level[lvl], 
		lwsc_msg[lwsc_status.msg], 
		lwsc_ctx[lwsc_status.ctx], 
		lwsc_status.p, buf);
}
