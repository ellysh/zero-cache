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

int hashmap_register_device( struct file_operations* fops )
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

int hashmap_unregister_device()
{
    cdev_del( &gDevice.chrdev );
    device_destroy( gDevice.class, gDevice.number );
    class_destroy( gDevice.class );
    unregister_chrdev_region( gDevice.number, 1 );
    return 0;
}

static int hashmap_open(struct inode *i, struct file *f)
{
  printk(KERN_INFO "hashmap: open()\n");
  return 0;
}

static int hashmap_close(struct inode *i, struct file *f)
{
  printk(KERN_INFO "hashmap: close()\n");
  return 0;
}

static long hashmap_ioctl(struct file *file, unsigned int command, unsigned long arg)
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

static struct file_operations hashmap_fops =
{
    .owner   = THIS_MODULE,
    .open    = hashmap_open,
    .release = hashmap_close,
    .unlocked_ioctl = hashmap_ioctl
};

static int __init hashmap_init(void)
{
    int rc;
    spin_lock_init(&gLock);
    rc = hashmap_register_device( &hashmap_fops );
    printk(KERN_INFO "hashmap: init rc=%d\n",rc);
    printk( "Please, create a dev file with 'mknod /dev/hashmap c %d 0'.\n", MAJOR(gDevice.number) );
    return rc;
}

static void __exit hashmap_exit(void) /* Destructor */
{
    int rc;
    rc = hashmap_unregister_device();
    printk(KERN_INFO "hashmap: exit rc=%d",rc);
}

module_init(hashmap_init);
module_exit(hashmap_exit);

