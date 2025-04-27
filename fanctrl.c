// fanctrl.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/tracepoint.h>
#include <trace/events/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Fan Control module with custom tracing");
MODULE_VERSION("0.1");

/* Define tracepoint */
#define CREATE_TRACE_POINTS
#include "fanctrl_tp.h"

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