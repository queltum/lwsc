#include "inc\lwsc_ctx.h"

const char *lwsc_ctx[LWSC_CTX_COUNT] = {
	"missing mantissa",
	"missing operator",
	"missing operand",
	"missing closing parenthesis \')\'",
	"missing opening parenthesis \'(\'",
	"empty parentheses are not allowed",
	"multiple decimal separators",
	"function \'%s\' does not support parameters",
	"function \'%s\' is not defined",
	"operator \'%c\' is not defined",
	"variable \'%c\' is not defined",
};