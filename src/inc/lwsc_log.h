#ifndef LWSC_LOG_H
#define LWSC_LOG_H

#include "lwsc_io.h"

extern void lwsc_panic(char mod, char msg);
extern void lwsc_abort(char mod, char msg, short where);

#endif
