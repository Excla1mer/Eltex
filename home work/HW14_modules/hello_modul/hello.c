#include <linux/module.h>
#include <linux/kernel.h>

//MODULE_LICENSE("GPLv2");
//MODULE_AUTHOR("Sergey SS");

int init_module(void){
	printk(KERN_INFO "Hello world\n");
	return 0;
}

void cleanup_module(void){
	printk(KERN_INFO "Goodbye world!\n");
}
