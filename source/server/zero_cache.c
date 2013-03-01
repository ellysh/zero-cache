#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

#include "zero_cache.h"

#define CLASS  "zero_cache_class"
#define DEVICE "zero_cache"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ilya Shpigor <petrsum@gmail.com>");
MODULE_DESCRIPTION("Kernel data cache module");

static struct Device
{
    dev_t number;
    struct cdev chrdev;
    struct class* class;
} gDevice;

static spinlock_t gLock;
static long gCache = 0;

int zc_register_device( struct file_operations* fops )
{
    if( alloc_chrdev_region(&gDevice.number, 0, 1, DEVICE ) < 0 )
        return -1;

    gDevice.class = class_create(THIS_MODULE, CLASS);
    if (gDevice.class == NULL)
    {
        unregister_chrdev_region(gDevice.number, 1);
        return -1;
    }

    if (device_create(gDevice.class, NULL, gDevice.number, NULL, "mynull") == NULL)
    {
        class_destroy(gDevice.class);
        unregister_chrdev_region(gDevice.number, 1);
        return -1;
    }

    cdev_init(&gDevice.chrdev, fops);
    if (cdev_add(&gDevice.chrdev, gDevice.number, 1) == -1)
    {
        device_destroy(gDevice.class, gDevice.number);
        class_destroy(gDevice.class);
        unregister_chrdev_region(gDevice.number, 1);
        return -1;
    }
    return 0;
}

int zc_unregister_device()
{
    cdev_del( &gDevice.chrdev );
    device_destroy( gDevice.class, gDevice.number );
    class_destroy( gDevice.class );
    unregister_chrdev_region( gDevice.number, 1 );
    return 0;
}

static int zc_open(struct inode *i, struct file *f)
{
  printk(KERN_INFO "zero_cache: open()\n");
  return 0;
}

static int zc_close(struct inode *i, struct file *f)
{
  printk(KERN_INFO "zero-cache: close()\n");
  return 0;
}

static long zc_ioctl(struct file *file, unsigned int command, unsigned long arg)
{
    spin_lock(&gLock);

    switch (command)
    {
    case IOCTL_SET_MSG:
        get_user(gCache, (long*)arg);
        //printk(KERN_INFO "SET");
        break;

    case IOCTL_GET_MSG:
        put_user(gCache, (long*)arg);
        //printk(KERN_INFO "GET");
        break;
    }

    spin_unlock(&gLock);

    return 0;
}

static struct file_operations zc_fops =
{
    .owner   = THIS_MODULE,
    .open    = zc_open,
    .release = zc_close,
    .unlocked_ioctl = zc_ioctl
};

static int __init zc_init(void)
{
    int rc;
    spin_lock_init(&gLock);
    rc = zc_register_device( &zc_fops );
    printk(KERN_INFO "zero_cache: init rc=%d\n",rc);
    printk( "Please, create a dev file with 'mknod /dev/zero_cache c %d 0'.\n", MAJOR(gDevice.number) );
    return rc;
}

static void __exit zc_exit(void)
{
    int rc;
    rc = zc_unregister_device();
    printk(KERN_INFO "zero_cache: exit rc=%d",rc);
}

module_init(zc_init);
module_exit(zc_exit);

