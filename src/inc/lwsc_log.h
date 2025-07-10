#ifndef LWSC_LOG_H
#define LWSC_LOG_H

#include "lwsc_msg.h"
#include "lwsc_ctx.h"

#define LWSC_LOG_BUF_SZ 1024

typedef enum {
	LWSC_LOG_LVL_LOG,
	LWSC_LOG_LEVEL_WARN,
	LWSC_LOG_LEVEL_ERROR,
	LWSC_LOG_LEVEL_COUNT
} lwsc_log_level;

struct LWSCStatus {
	char *p;
	short where;
	lwsc_msg_id msg;
	lwsc_ctx_id ctx;
};

extern struct LWSCStatus lwsc_status;

extern void lwsc_log(lwsc_log_level lvl);
extern void lwsc_status_update(char *p, short where, 
	lwsc_msg_id msg, lwsc_ctx_id ctx);

#endif