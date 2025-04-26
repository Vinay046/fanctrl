// fanctrl.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init fanctrl_init(void)
{
    printk(KERN_INFO "Hello, Loading fanctrl kernel module\n");
    return 0;
}

static void __exit fanctrl_exit(void)
{
    printk(KERN_INFO "Goodbye, Unloading fanctrl kernel module\n");
}

module_init(fanctrl_init);
module_exit(fanctrl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vinay");
MODULE_DESCRIPTION("Kernel Module to control fan speed based on CPU temps");

