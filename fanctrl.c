// fanctrl.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/tracepoint.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Fan Control module with custom tracing");
MODULE_VERSION("0.1");

/* Define tracepoint system */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM fanctrl

/* 
 * For in-file tracepoints, we need to specify the include path
 * to be the current directory
 */
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE fanctrl

/* 
 * Define the tracepoint before including define_trace.h
 * First we need the tracepoint definition
 */
#if !defined(_FANCTRL_TP_H) || defined(TRACE_HEADER_MULTI_READ)
#define _FANCTRL_TP_H

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

/* 
 * Now create the tracepoint function
 * This must be done after the tracepoint definition but before the module code
 */
#define CREATE_TRACE_POINTS
#include <trace/define_trace.h>

/* Module code starts here */
static int __init fanctrl_init(void)
{
    printk(KERN_INFO "FanCtrl Module: Initializing\n");
    
    // Emit a trace event
    trace_fanctrl_event("Module initialized");
    
    // Emit another trace event
    trace_fanctrl_event("Hello from fan controller!");
    
    return 0;
}

static void __exit fanctrl_exit(void)
{
    printk(KERN_INFO "FanCtrl Module: Exiting\n");
    trace_fanctrl_event("Module exiting");
}

module_init(fanctrl_init);
module_exit(fanctrl_exit);