/* fanctrl_tp.h */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM fanctrl

#if !defined(_FANCTRL_TP_H) || defined(TRACE_HEADER_MULTI_READ)
#define _FANCTRL_TP_H

#include <linux/tracepoint.h>

TRACE_EVENT(fanctrl_event,
    TP_PROTO(const char *message),
    TP_ARGS(message),
    TP_STRUCT__entry(
        __string(message, message)
    ),
    TP_fast_assign(
        __assign_str(message, message);
    ),
    TP_printk("FanCtrl: %s", __get_str(message))
);

#endif /* _FANCTRL_TP_H */

/* This part must be outside the header guard */
#include <trace/define_trace.h>