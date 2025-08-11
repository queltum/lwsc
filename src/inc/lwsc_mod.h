#ifndef LWSC_MOD_H
#define LWSC_MOD_H

typedef enum {
	LWSC_MOD_NULL,
	LWSC_MOD_MEM,
	LWSC_MOD_HANDLER,
	LWSC_MOD_LEXER,
	LWSC_MOD_PARSER,
	LWSC_MOD_COUNT,
} lwsc_mod_id;

extern const char *lwsc_mod[LWSC_MOD_COUNT];

#endif