#include <string.h>

#include "inc\lwsc_log.h"
#include "inc\lwsc_types.h"
#include "inc\lwsc_handler.h"

#define LWSC_HANDLER_BUF_SZ 1024

#define LWSC_ST2UI32(st) (*(unsigned int *)&st)
#define LWSC_RESET_ST(st)(LWSC_ST2UI32(st) = 0)
#define LWSC_RESET_FLAGS(st)(LWSC_ST2UI32(st) &= 0xFFFFFC00)

static struct {
	unsigned lvl: 10, offset: 12,
		is_number: 1, is_operator: 1, 
		is_fn: 1, is_fn_param: 1, is_fn_arg: 1, 
		is_def: 1, is_open_paren: 1, is_close_paren: 1;
} lwsc_state;

static char *bp, *sp;
static char lwsc_buf[LWSC_HANDLER_BUF_SZ];

char *lwsc_handle(const char *s) {
	LWSC_RESET_STATE(lwsc_state);

	for (bp = lwsc_buf, sp = s; *sp != '\n';) {
		state.offset = bp - lwsc_buf;

		if (lwsc_isspace(*sp))
			++sp;
		if (lwsc_isparenthesis(*sp)) {
			if (state.is_number) {
				lwsc_status_update(
					LWSC_MSG_INVALID_EXPR, 
					LWSC_CTX_MISSING_OPERATOR,
					state.offset, s);
				goto _EL;
			}

			switch (*bp - '(') {
			case 0:
				state.is_open_paren = 1;
				++state.lvl;
				break;
			case 1:
				if (!state.lvl) {
					lwsc_status_update(
						LWSC_MSG_UNBALANCED_PAREN, 
						LWSC_CTX_MISSING_OPEN_PAREN,
						state.offset, s);
					goto _EL;			
				}
				if (state.offset > 0 && *(bp - 1) == '(') {
					lwsc_status_update(
						LWSC_MSG_UNBALANCED_PAREN, 
						LWSC_CTX_MISSING_OPEN_PAREN,
						state.offset, s);
					goto _EL;
				}
				state.is_close_paren = 1;
				--state.lvl;
				break;
			}
			*bp++ = *sp++;
		}
		/* NUMBER HANDLER */
		if (lwsc_isdigit(*bp)) {
			if (state.is_number) {
				lwsc_status_update(
					LWSC_MSG_INVALID_EXPR, 
					LWSC_CTX_MISSING_OPERATOR,
					offset, s);
				goto _EL;
			}
			LWSC_RESET_FLAGS(state);

			state.is_number = 1;
			state.
_L1:		while (lwsc_isdigit(*bp))
				*tmp_bp++ = *bp++;

			if (lwsc_isseparator(*bp)) {
				if (st.opd_mantissa) {
					lwsc_panic(1, 6, lwsc_iobuf, bp - lwsc_iobuf);
					return NULL;
				}

				if (lwsc_isdigit(*(++bp)))
					st.opd_mantissa = 1;
				else {
					lwsc_panic(1, 0, lwsc_iobuf, bp - lwsc_iobuf);
					return NULL;
				}
				goto _L1;
			}
		}

		switch (*bp) {
			case '+':
				break;
			case '-': 
			case '*': 
			case ':': case '/': 
			case '^': 
			case '%':
				break;
		}
	}

	return lwsc_buf;
_EL:
	lwsc_log(LWSC_LOG_LEVEL_WARN);
	return NULL;
}