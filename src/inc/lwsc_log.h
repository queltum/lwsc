#ifndef LWSC_LOG_H
#define LWSC_LOG_H

#include "lwsc_msg.h"
#include "lwsc_ctx.h"
#include "lwsc_mod.h"

typedef enum {
	LWSC_LOG,
	LWSC_WARN,
	LWSC_ERROR,
	LWSC_LOG_COUNT
} lwsc_log_level_id;

typedef struct {
	unsigned lvl: 2, mod: 4, msg: 4, ctx: 6, where: 10, render: 2, resv: 4;
} lwsc_log_status;

extern lwsc_log_status lwsc_status;

extern void lwsc_panic(char mod, char msg);
extern void lwsc_abort(char mod, char msg, char ctx, short where);

extern void lwsc_log_cls(void);
extern const char *lwsc_log_get(void);

#endif
