#include "inc\lwsc_log.h"

enum { LWSC_LOG, LWSC_WARN, LWSC_ERROR, LWSC_LVL_COUNT };
enum { LWSC_ALLOC, LWSC_HANDLER, LWSC_LEXER, LWSC_PARSER };

static const char *lwsc_str = "@lwsc_@: @;";

static const char *lwsc_lvl[LWSC_LVL_COUNT] = {
	"log!", "warn?", "error??"
}

static const char *lwsc_mod[LWSC_MOD_COUNT] = {
	"alloc", "handler", "lexer", "parser"
};

static const char *lwsc_msg[LWSC_MSG_COUNT] = {
	"no-message",
	"invalid-expression",
	"unknown-object",
	"no-memory",
	"hpt-overflow",
	"unavaliable-header",
};

static struct {
	unsigned short mod: 2, msg: 3, tag: 10, updated: 1;
} lwsc_status;


void lwsc_panic(char mod, char msg) {
	char *bp, pos; 
	const char *pp, *sp;

	lwsc_status.mod = mod;
	lwsc_status.msg = msg;

	bp = lwsc_page(LWSC_PAGE_LOG);
	pp = lwsc_log_pattern[LWSC_NO_CTX];
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

void lwsc_abort(char mod, char msg, char ctx, short where) {
	return;
}
