#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h> 
MODULE_LICENSE("GPLv2");
MODULE_AUTHOR("Sergey SS");

static ssize_t my_read(struct file *, char *, size_t, loff_t *);
static ssize_t my_write(struct file *, const char *, size_t, loff_t *);

#define DEVICE_NAME "my_module"

static int Major;
static char msg_buff[80];

static ssize_t my_read(struct file *filp, char *buffer, size_t length, loff_t * offset) {
	printk(KERN_INFO "You What read my_modul\n");
	return 0;
}

static ssize_t my_write(struct file *filp, const char *user_buff, size_t len, loff_t * off)
{
	int ret;
	ret = simple_write_to_buffer(msg_buff, sizeof(msg_buff), off, user_buff, len);
	if (!ret)
		return -EFAULT;
	printk(KERN_INFO "You whan write my_modul: %s\n", msg_buff);
	return ret < 0 ? ret : len;
}

static struct file_operations fops = {
        .read = my_read,
        .write = my_write
};

int __init init_module(void){
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if(Major < 0 ){
		printk(KERN_INFO "Error of register_chrdev\n");
		return Major;
	}

	printk(KERN_INFO "Hello world, my Major %d\n", Major);
	return 0;
}

void __exit cleanup_module(void){
	unregister_chrdev(Major, DEVICE_NAME);
	printk(KERN_INFO "Goodbye world!\n");
}


