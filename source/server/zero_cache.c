#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#include "zero_cache.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ilya Shpigor <petrsum@gmail.com>");
MODULE_DESCRIPTION("Kernel data cache module");

#define CLASS       "zero_cache_class"
#define DEVICE      "zero_cache"
#define CACHE_SIZE  100000

static struct Device
{
    dev_t number;
    struct cdev chrdev;
    struct class* class;
} gDevice;

static spinlock_t gLock;

static cell_t gCache[CACHE_SIZE];

static long zc_ioctl(struct file *file, unsigned int command, unsigned long arg)
{
    struct Package* package;
    package = (struct Package*)arg;

    if ( (package->offset) < 0 || (CACHE_SIZE < package->offset) )
        return -1;

    spin_lock(&gLock);

    switch (command)
    {
    case IOCTL_SET_MSG:
        printk(KERN_INFO "SET");
        get_user(gCache[package->offset], &package->data);
        break;

    case IOCTL_GET_MSG:
        printk(KERN_INFO "GET");
        put_user(gCache[package->offset], &package->data);
        break;
    }

    spin_unlock(&gLock);

    return 0;
}

int zc_register_device(struct file_operations* fops)
{
    if ( alloc_chrdev_region(&gDevice.number, 0, 1, DEVICE ) < 0 )
        return -1;

    gDevice.class = class_create(THIS_MODULE, CLASS);
    if ( gDevice.class == NULL )
    {
        unregister_chrdev_region(gDevice.number, 1);
        return -1;
    }

    if ( device_create(gDevice.class, NULL, gDevice.number, NULL, DEVICE) == NULL )
    {
        class_destroy(gDevice.class);
        unregister_chrdev_region(gDevice.number, 1);
        return -1;
    }

    cdev_init(&gDevice.chrdev, fops);
    if ( cdev_add(&gDevice.chrdev, gDevice.number, 1) == -1 )
    {
        device_destroy(gDevice.class, gDevice.number);
        class_destroy(gDevice.class);
        unregister_chrdev_region(gDevice.number, 1);
        return -1;
    }
    return 0;
}

static struct file_operations zc_fops =
{
    .owner   = THIS_MODULE,
    .unlocked_ioctl = zc_ioctl
};

static int __init zc_init(void)
{
    int rc;

    spin_lock_init(&gLock);
    rc = zc_register_device(&zc_fops);
    printk(KERN_INFO "zero_cache: init rc=%d\n", rc);
    printk("Please, create a dev file with 'mknod /dev/zero_cache c %d 0'.\n", MAJOR(gDevice.number));
    return rc;
}

static void __exit zc_exit(void)
{
    cdev_del(&gDevice.chrdev);
    device_destroy(gDevice.class, gDevice.number);
    class_destroy(gDevice.class);
    unregister_chrdev_region(gDevice.number, 1);

    printk(KERN_INFO "zero_cache: exit\n");
}

module_init(zc_init);
module_exit(zc_exit);
