#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>

#include <linux/debugfs.h>

static struct dentry *my_dentry, *f1_dentry, *f2_dentry;
int filevalue;

ssize_t my_read(struct file *fp, char __user *ubuf, size_t len, loff_t *pos)
{
	pr_warn("my_read\n");
	return 0;
}

ssize_t my_write(struct file *fp, const char __user *ubuf, size_t len, loff_t *pos)
{
	pr_warn("my_write\n");
	return len;
}

static const struct file_operations myfops = {
	.read = my_read,
	.write = my_write
};

int __init my_init(void)
{
	my_dentry = debugfs_create_dir("eudyptula", NULL);
	
	f1_dentry = debugfs_create_file("jiffies", 0644, my_dentry, &filevalue, &myfops);
	f2_dentry = debugfs_create_file("foo", 0644, my_dentry, &filevalue, &myfops);

	pr_warn("Hello World!\n");
	return 0;
}

void __exit my_exit(void)
{
	debugfs_remove_recursive(my_dentry);
	pr_warn("exit module\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello module");
MODULE_AUTHOR("myself");


