// fanctrl.c
#define pr_fmt(fmt) "fanctrl: " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vinay");
MODULE_DESCRIPTION("Kernel Module to control fan speed based on CPU temps");
MODULE_VERSION("0.2");

#define MAX_THERMAL_ZONES 8

static struct kobject *fanctrl_kobj;
static int fan_status = 0; // 0 = OFF, 1 = ON

// --- Helper to read thermal_zoneX/temp ---
static int read_thermal_zone_temp(int zone, int *temp)
{
    struct file *f;
    char path[64];
    char buf[16];
    loff_t pos = 0;
    ssize_t ret;

    snprintf(path, sizeof(path), "/sys/class/thermal/thermal_zone%d/temp", zone);

    f = filp_open(path, O_RDONLY, 0);
    if (IS_ERR(f))
        return PTR_ERR(f);

    ret = kernel_read(f, buf, sizeof(buf) - 1, &pos);
    if (ret < 0) {
        filp_close(f, NULL);
        return ret;
    }

    buf[ret] = '\0';
    *temp = simple_strtol(buf, NULL, 10);

    filp_close(f, NULL);
    return 0;
}

// --- Sysfs Show Handlers ---

// Show all thermal zone temperatures
static ssize_t cpu_temp_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int temp;
    int ret;
    ssize_t len = 0;

    len += sprintf(buf + len, "=== Fan Controller Status ===\n");

    for (int i = 0; i < MAX_THERMAL_ZONES; i++) {
        ret = read_thermal_zone_temp(i, &temp);
        if (ret == 0)
            len += sprintf(buf + len, "thermal_zone%d: %d.%03d C\n", i, temp / 1000, temp % 1000);
    }

    len += sprintf(buf + len, "Fan Status: %s\n", fan_status ? "ON" : "OFF");
    len += sprintf(buf + len, "==============================\n");

    return len;
}

// Show fan status
static ssize_t fan_control_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", fan_status);
}

// Set fan status manually
static ssize_t fan_control_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int new_status;

    if (kstrtoint(buf, 10, &new_status) < 0)
        return -EINVAL;

    if (new_status != 0 && new_status != 1)
        return -EINVAL;

    fan_status = new_status;

    if (fan_status)
        trace_printk("[fanctrl] Fan turned ON\n");
    else
        trace_printk("[fanctrl] Fan turned OFF\n");

    return count;
}

// --- Sysfs Attributes ---

static struct kobj_attribute cpu_temp_attr = __ATTR_RO(cpu_temp);
static struct kobj_attribute fan_control_attr = __ATTR_RW(fan_control);

static struct attribute *fanctrl_attrs[] = {
    &cpu_temp_attr.attr,
    &fan_control_attr.attr,
    NULL,
};

static struct attribute_group fanctrl_attr_group = {
    .attrs = fanctrl_attrs,
};

// --- Module Init/Exit ---

static int __init fanctrl_init(void)
{
    int ret;

    pr_info("Loading Fan Control Kernel Module\n");

    fanctrl_kobj = kobject_create_and_add("fanctrl", kernel_kobj);
    if (!fanctrl_kobj)
        return -ENOMEM;

    ret = sysfs_create_group(fanctrl_kobj, &fanctrl_attr_group);
    if (ret) {
        pr_err("Failed to create sysfs group\n");
        kobject_put(fanctrl_kobj);
    } else {
        pr_info("Sysfs group created successfully\n");
    }

    return ret;
}

static void __exit fanctrl_exit(void)
{
    pr_info("Unloading Fan Control Kernel Module\n");
    kobject_put(fanctrl_kobj);
}

module_init(fanctrl_init);
module_exit(fanctrl_exit);
