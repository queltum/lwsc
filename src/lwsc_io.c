#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "inc/lwsc_io.h"
#include "inc/lwsc_types.h"

#define LWSC_ST2UI16(st) (*(unsigned short *)&st)
#define LWSC_RESET_ST(st)(LWSC_ST2UI16(st) = 0)
#define LWSC_RESET_FLAGS(st)(LWSC_ST2UI16(st) & 0xFF80)

static char lwsc_iobuf[LWSC_IOBUF_SZ];

static char *lwsc_msg[] = {
	"unbalanced parentheses",
	"invalid number format",
	"invalid expression",
	"unknown operator",
	"unknown operand",
	"unknown function",
}, *lwsc_ctx[] = {
	"missing mantissa",
	"missing operator",
	"missing operand",
	"missing closing parenthesis \')\'",
	"missing opening parenthesis \'(\'",
	"empty parentheses are not allowed",
	"multiple decimal separators",
	"function \'%s\' is not defined",
	"function \'%s\' does not support parameters",
	"operator \'%c\' is not defined",
	"variable \'%c\' is not defined",
};

void lwsc_panic(char msg_id, char ctx_id, char *p, short where) {
	char buf[where + 1];
	
	memset(buf, ' ', where);
	buf[where] = '^';

	fprintf(stdout, "\n$lwsc-warn %s: %s at\n> %s  ", 
		lwsc_msg[msg_id], lwsc_ctx[ctx_id], p);
	fwrite(buf, sizeof(char), where + 1, stdout);
}

static char *lwsc_handle(void) {
	char *bp, *tmp_bp;
	char buf[1024];

	struct {
		unsigned short lvl: 9, op_unary: 1, 
			opd_mantissa: 1, is_opd: 1, is_fn: 1, 
			fn_param: 1, fn_arg: 1, is_def: 1;
	} st;

	LWSC_RESET_ST(st);

	for (bp = lwsc_iobuf, tmp_bp = buf; *bp != '\n';) {
		LWSC_RESET_FLAGS(st);
		if (lwsc_isspace(*bp)) {
			++bp;
			continue;
		}
		if (lwsc_isparenthesis(*bp)) {
			switch (*bp - '(') {
			case 0:
				++st.lvl;
				break;
			case 1:
				if (!st.lvl) {
					lwsc_panic(2, 4, lwsc_iobuf, bp - lwsc_iobuf);
					return NULL;
				}
				if (*tmp_bp == '(') {
					lwsc_panic(2, 5, lwsc_iobuf, bp - lwsc_iobuf);
					return NULL;
				}
				--st.lvl;
				break;
			}
			*tmp_bp++ = *bp++;
			continue;
		}
		/* NUMBER HANDLER */
		if (lwsc_isdigit(*bp)) {
			LWSC_RESET_FLAGS(st);

			st.is_opd = 1;
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
			continue;
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

	memcpy(lwsc_iobuf, buf, LWSC_IOBUF_SZ);
	return lwsc_iobuf;
}

char *lwsc_readin(void) {
	fgets(lwsc_iobuf, LWSC_IOBUF_SZ, stdin);
	return lwsc_handle();
}

