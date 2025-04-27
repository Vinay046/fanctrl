#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vinay");
MODULE_DESCRIPTION("Fan Control module with custom tracing");
MODULE_VERSION("0.1");

/* Tracepoint setup */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM fanctrl

#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE fanctrl

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

#define CREATE_TRACE_POINTS
#include <trace/define_trace.h>

/* Actual module code */
static int __init fanctrl_init(void)
{
    pr_info("FanCtrl Module: Initializing\n");
    
    trace_fanctrl_event("Module initialized");
    trace_fanctrl_event("Hello from fan controller!");
    
    return 0;
}

static void __exit fanctrl_exit(void)
{
    pr_info("FanCtrl Module: Exiting\n");
    trace_fanctrl_event("Module exiting");
}

module_init(fanctrl_init);
module_exit(fanctrl_exit);
