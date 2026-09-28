#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/cdev.h>

#define DEVICE_NAME "smartlab"

static dev_t device_number;
static struct cdev smartlab_cdev;
static struct class *smartlab_class;

static char device_message[100] = "SmartLab Guardian: Device Ready\n";

/* Open the character device */
static int smartlab_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "SmartLab Guardian: device opened\n");
    return 0;
}

/* Read data from kernel space to user space */
static ssize_t smartlab_read(
    struct file *file,
    char __user *buffer,
    size_t length,
    loff_t *offset)
{
    int message_length = strlen(device_message);

    if (*offset >= message_length)
        return 0;

    if (length > message_length - *offset)
        length = message_length - *offset;

    if (copy_to_user(buffer, device_message + *offset, length))
        return -EFAULT;

    *offset += length;

    printk(KERN_INFO "SmartLab Guardian: data read\n");

    return length;
}

/* Write data from user space to kernel space */
static ssize_t smartlab_write(
    struct file *file,
    const char __user *buffer,
    size_t length,
    loff_t *offset)
{
    if (length >= sizeof(device_message))
        length = sizeof(device_message) - 1;

    if (copy_from_user(device_message, buffer, length))
        return -EFAULT;

    device_message[length] = '\0';

    printk(KERN_INFO "SmartLab Guardian: data written\n");

    return length;
}

/* Close the character device */
static int smartlab_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "SmartLab Guardian: device closed\n");
    return 0;
}

/* File operations */
static struct file_operations smartlab_fops =
{
    .owner = THIS_MODULE,
    .open = smartlab_open,
    .read = smartlab_read,
    .write = smartlab_write,
    .release = smartlab_release
};

/* Module initialization */
static int __init smartlab_init(void)
{
    int result;

    printk(KERN_INFO "SmartLab Guardian: module loading\n");

    result = alloc_chrdev_region(
        &device_number,
        0,
        1,
        DEVICE_NAME
    );

    if (result < 0)
    {
        printk(KERN_ERR "SmartLab Guardian: device number allocation failed\n");
        return result;
    }

    cdev_init(&smartlab_cdev, &smartlab_fops);
    smartlab_cdev.owner = THIS_MODULE;

    result = cdev_add(&smartlab_cdev, device_number, 1);

    if (result < 0)
    {
        unregister_chrdev_region(device_number, 1);
        printk(KERN_ERR "SmartLab Guardian: cdev registration failed\n");
        return result;
    }

    smartlab_class = class_create(DEVICE_NAME);

    if (IS_ERR(smartlab_class))
    {
        cdev_del(&smartlab_cdev);
        unregister_chrdev_region(device_number, 1);
        return PTR_ERR(smartlab_class);
    }

    if (IS_ERR(device_create(
        smartlab_class,
        NULL,
        device_number,
        NULL,
        DEVICE_NAME)))
    {
        class_destroy(smartlab_class);
        cdev_del(&smartlab_cdev);
        unregister_chrdev_region(device_number, 1);
        return -1;
    }

    printk(KERN_INFO "SmartLab Guardian: /dev/%s created\n", DEVICE_NAME);

    return 0;
}

/* Module cleanup */
static void __exit smartlab_exit(void)
{
    device_destroy(smartlab_class, device_number);
    class_destroy(smartlab_class);

    cdev_del(&smartlab_cdev);
    unregister_chrdev_region(device_number, 1);

    printk(KERN_INFO "SmartLab Guardian: module unloaded\n");
}

module_init(smartlab_init);
module_exit(smartlab_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sneha Burma");
MODULE_DESCRIPTION("SmartLab Guardian Character Device Driver");
