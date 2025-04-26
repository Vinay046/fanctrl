#undef TRACE_SYSTEM
#define TRACE_SYSTEM fanctrl

#if !defined(_TRACE_FANCTRL_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_FANCTRL_H

#include <linux/tracepoint.h>

TRACE_EVENT(cpu_temp_reported,
    TP_PROTO(int temp),
    TP_ARGS(temp),
    TP_STRUCT__entry(
        __field(int, temp)
    ),
    TP_fast_assign(
        __entry->temp = temp;
    ),
    TP_printk("CPU temperature reported: %d C", __entry->temp)
);

#endif /* _TRACE_FANCTRL_H */

#include <trace/define_trace.h>
