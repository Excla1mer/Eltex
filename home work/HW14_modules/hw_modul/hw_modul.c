#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/rwlock.h>
MODULE_LICENSE("GPLv2");
MODULE_AUTHOR("Sergey SS");

static ssize_t my_read(struct file *, char *, size_t, loff_t *);
static ssize_t my_write(struct file *, const char *, size_t, loff_t *);

#define DEVICE_NAME "my_module"

static int Major;
static char msg_buff[80]="My msg buff\0\n";
static rwlock_t lock;
/*
 * Функция обработки считывания из модуля. пример cat /dev/my_module
 * kernel space ---msg_buff----> user space
 */
static ssize_t my_read(struct file *filp, char __user *user_buff, size_t length, loff_t * off) {
	size_t rc;
	read_lock(&lock);
	rc = simple_read_from_buffer(user_buff, length, off, msg_buff, 80); // /fs/libfs.c
	read_unlock(&lock);
	if(rc > 0)
		pr_info(KERN_INFO "You Whant read my_modul\n");
	return rc;
}
/*
 * Функция по обработке записи в модуль. пример echo "my message" > /dev/my_module
 * kernel space <----"my message"---- user space
 */
static ssize_t my_write(struct file *filp, const char __user *user_buff, size_t len, loff_t * off)
{
	int ret;
	memset(msg_buff, 0, 80);
	if(len > 80)
		return -EINVAL;
	write_lock(&lock);
	ret = simple_write_to_buffer(msg_buff, sizeof(msg_buff), off, user_buff, len);
	write_unlock(&lock);
	if (!ret)
		return -EFAULT;
	pr_info(KERN_INFO "You whan write my_modul: %s\n", msg_buff);
	return ret;
}
/*
 * Переобределяем значения структуры 
 * */
static struct file_operations fops = {
        .owner = THIS_MODULE,
	.read = my_read,
        .write = my_write
};

int __init init_module(void){
	Major = register_chrdev(0, DEVICE_NAME, &fops); // Получаем от ядра свободный мажорный номер
	if(Major < 0 ){
		pr_info(KERN_INFO "Error of register_chrdev\n");
		return Major;
	}

	pr_info(KERN_INFO "Hello world, my Major %d\n", Major);
	return 0;
}

void __exit cleanup_module(void){
	unregister_chrdev(Major, DEVICE_NAME); // Высвобождаем мажорный номер
	pr_info(KERN_INFO "Goodbye world!\n");
}


