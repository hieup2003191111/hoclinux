#include<linux/module.h>
#include<linux/kernel.h>
static  int hello_driver_init(void){
    printk("hello driver was loaded \n");
    return 0;
}
static void hello_driver_exit(void){
    printk("hello driver stopped \n");
}
module_init(hello_driver_init);
module_exit(hello_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("hello driver");
MODULE_AUTHOR("Hieu");