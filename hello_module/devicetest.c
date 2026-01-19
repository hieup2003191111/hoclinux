#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>

static int major;
static struct class *hieu_class = NULL;
static struct device *hieu_device = NULL;
static struct file_operations fops= {
    .owner=THIS_MODULE,
};

static int __init hieu_init(void) {
    printk( "Hieu: load driver...\n");
    major = register_chrdev(0, "hieu_dev", &fops);
    if (major < 0) {
        printk( "Hieu: error Major\n");
        return major;
    }
    hieu_class = class_create("hieu_class");
    if (IS_ERR(hieu_class)) {
        unregister_chrdev(major, "hieu_dev");
        return PTR_ERR(hieu_class);
    }
    hieu_device = device_create(hieu_class, NULL, MKDEV(major, 0), NULL, "hieu_device");
    if (IS_ERR(hieu_device)) {
        class_destroy(hieu_class);
        unregister_chrdev(major, "hieu_dev");
        return PTR_ERR(hieu_device);
    }
    printk(KERN_INFO "Hieu: create /dev/hieu_device and Major %d\n", major);
    return 0;
}
static void __exit hieu_exit(void) {
    device_destroy(hieu_class, MKDEV(major, 0));
    class_destroy(hieu_class);
    unregister_chrdev(major, "hieu_dev");
    printk("Hieu:  exit driver\n");
}
module_init(hieu_init);
module_exit(hieu_exit);
MODULE_LICENSE("GPL");