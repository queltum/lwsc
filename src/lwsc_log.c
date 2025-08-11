#include "inc\lwsc_log.h"
#include "inc\lwsc_mem.h"

typedef enum {
	LWSC_RENDER_FULL,
	LWSC_RENDER_NO_CTX,
	LWSC_RENDER_NO_MOD,
	LWSC_RENDER_COUNT
} lwsc_log_render_id;

static const char *lwsc_log_pattern[LWSC_RENDER_COUNT] = {
	"lwsc_@$@/@: @;", "lwsc_@$@/@;", "lwsc_@$@;"
};

static const char *lwsc_log_level[LWSC_LOG_COUNT] = { 
	"log", "warn", "error" 
};

static void lwsc_log_render_no_ctx(void) {
	char *bp, pos; 
	const char *pp, *sp;

	bp = lwsc_mem;
	pp = lwsc_log_pattern[LWSC_RENDER_NO_CTX];
	pos = 0;

	while (*pp)
		if (*pp == '@') {
			if (pos == 0)
				sp = lwsc_log_level[lwsc_status.lvl];
			else if (pos == 1)
				sp = lwsc_mod[lwsc_status.mod];
			else if (pos == 2)
				sp = lwsc_msg[lwsc_status.msg];
			else
				return;
			while (*sp)
				*bp++ = *sp++;
			pos++;
			pp++;
		} else
			*bp++ = *pp++;
	*bp = '\0';
}

lwsc_log_status lwsc_status;

void lwsc_panic(char mod, char msg) {
	lwsc_status.lvl = LWSC_WARN;
	lwsc_status.mod = mod;
	lwsc_status.msg = msg;
	lwsc_log_render_no_ctx();
}

void lwsc_abort(char mod, char msg, char ctx, short where) {
	return;
}

const char *lwsc_log_get() {
	return lwsc_mem;
}
