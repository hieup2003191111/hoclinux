#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>       
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <asm/uaccess.h>
//#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>
#define DRIVER_NAME "hieu_driver"
#define DEVICE_COUNT 1
//#define LED_GPIO 23
static struct gpio_desc *led_gpio;
//khai bao luu major minor number
static dev_t dev_num;
//khai bao struct cdev
static struct cdev my_cdev;
static struct class *my_class;
static struct device *my_device;
//dinh nghia file operations
static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "%s: Device opened successfully.\n", DRIVER_NAME);
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    printk(KERN_INFO "%s: Device read operation called. Count: %zu\n", DRIVER_NAME, count);
    return 0; 
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    char command;
    int value;
    printk(KERN_INFO "%s: Device write operation called. Count: %zu\n", DRIVER_NAME, count);
    if(count > 0){
        if(copy_from_user(&command,buf,1)){
            return -EFAULT;
        }
        if(command == '1'){
            value =1;//high
            printk(KERN_INFO "%s : '1' is received.Led on\n",DRIVER_NAME);
        } else if (command == '0'){
            value=0;//low
            printk(KERN_INFO"%s command '0' is received.led off\n",DRIVER_NAME);
        } else {
            printk(KERN_WARNING "command unvailble \n");
            return -EINVAL;
        }
        //gpio_set_value(LED_GPIO,value);
        if(led_gpio){
            gpiod_set_value_cansleep(led_gpio,value);
        } else {
            printk(KERN_ERR "%s: LED GPIO Description is null \n",DRIVER_NAME);
            return -EIO;
        }
    }
    return count; 
}

static int my_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "%s: Device closed.\n", DRIVER_NAME);
    return 0;
}

//dang ki operations
static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .read = my_read,
    .write = my_write,
    .release = my_release,

};

//khoi tao device file
static int __init chardev_init(void)
{
    int ret;
    
    ret = alloc_chrdev_region(&dev_num, 0, DEVICE_COUNT, DRIVER_NAME);
    if (ret < 0) {
        printk(KERN_ERR "%s: Failed to allocate device number.\n", DRIVER_NAME);
        return ret;
    }

    printk(KERN_INFO "%s: Registered with Major: %d, Minor: %d\n", DRIVER_NAME, MAJOR(dev_num), MINOR(dev_num));

    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;

    //dang ki driver character
    ret = cdev_add(&my_cdev, dev_num, DEVICE_COUNT);
    if (ret < 0) {
        printk(KERN_ERR "%s: Failed to add cdev.\n", DRIVER_NAME);
        unregister_chrdev_region(dev_num, DEVICE_COUNT);
        return ret;
    }
    //tao device file
    my_class = class_create(DRIVER_NAME);
    if (IS_ERR(my_class)) {
        printk(KERN_ERR "%s: Failed to create device class.\n", DRIVER_NAME);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, DEVICE_COUNT);
        return PTR_ERR(my_class);
    }
    my_device = device_create(my_class, NULL, dev_num, NULL, DRIVER_NAME);
    if (IS_ERR(my_device)) {
        printk(KERN_ERR "%s: Failed to create device.\n", DRIVER_NAME);
        class_destroy(my_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, DEVICE_COUNT);
        return PTR_ERR(my_device);
    }
    //dung dt lay gpio descriptior
    struct device_node *np;
    np= of_find_compatible_node(NULL,NULL,"hieu,simple-led");
    if(!np){
        printk(KERN_ERR "%s:failed to find dt node 'hieu,simple-led' \n",DRIVER_NAME);
        ret = -ENODEV;
        goto err_find_node;
    }
    //lay gpio descriptor tu thuoc tinh
led_gpio = gpiod_get(NULL, "led-gpio", GPIOD_OUT_LOW);    if (IS_ERR(led_gpio)) {
        ret = PTR_ERR(led_gpio);
        printk(KERN_ERR "%s: Failed to get LED GPIO from DT. Error: %d\n", DRIVER_NAME, ret);
        goto err_get_gpio;
    }
    printk(KERN_INFO "%s: LED GPIO acquired successfully via Device Tree.\n", DRIVER_NAME);
    
    // Khai báo nhãn lỗi (Cần thiết cho cấu trúc goto)
    goto success;

    err_get_gpio:
    of_node_put(np);
err_find_node:
    device_destroy(my_class,dev_num);
    class_destroy(my_class);
    cdev_del(&my_cdev);  
    unregister_chrdev_region(dev_num, DEVICE_COUNT);
    return ret;

success:
    of_node_put(np); // Giải phóng tham chiếu node
    printk(KERN_INFO "%s: Module initialized successfully.\n", DRIVER_NAME);
    return 0;
}
//xoa device file
static void __exit chardev_exit(void)
{
    if (led_gpio) {
        gpiod_put(led_gpio);
        printk(KERN_INFO "%s: LED GPIO Descriptor released.\n", DRIVER_NAME);
    }
    
    device_destroy(my_class,dev_num);
    class_destroy(my_class);
    cdev_del(&my_cdev);
    
    unregister_chrdev_region(dev_num, DEVICE_COUNT);
    
    printk(KERN_INFO "%s: Module exited successfully. Device numbers released.\n", DRIVER_NAME);
}

module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A basic Character Driver example.");