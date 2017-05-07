#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>

#define MAX_LEN		4096

int read_info(char *page, char **start, off_t off, int count, int *eof, void *data);
ssize_t write_info(struct file *filp, const char __user *buff, unsigned long len, void *data);

static struct proc_dir_entry *proc_entry;
static char *info;
static int write_index;
static int read_index;

static char procfs_buffer[MAX_LEN];
static unsigned long procfs_buffer_size = 0;


int init_module(void)
{
	int ret = 0;

	//allocated memory space for the proc entry
	info = (char *)vmalloc( MAX_LEN );
	memset(info, 0, MAX_LEN);

	//create the entry
	proc_entry = create_proc_entry("test_proc", 0644, NULL);

	if(proc_entry == NULL)
	{
		remove_proc_entry("test_proc", proc_entry);
		printk(KERN_ALERT "Could not init.\n");
		return -ENOMEM;
	} 

	//write_index = 0;
	//read_index = 0;
	//register the write and read callback functions
	proc_entry->read_proc = read_info;
	proc_entry->write_proc = write_info;
	//proc_entry->owner = THIS_MODULE;
	proc_entry->mode = S_IFREG| S_IRUGO;
	proc_entry->uid = 0;
	proc_entry->gid = 0;
	proc_entry->size = 37;
	printk(KERN_INFO "test_proc created.\n");

	return ret;
}

void cleanup_module(void)
{
	//remove the proc entry and free info space
	remove_proc_entry("test_proc", proc_entry);
	printk(KERN_INFO "test_proc removed.\n");
}

int write_info(struct file *filp, const char __user *buff, unsigned long len, void *data)
{
	//copy written data from user space and save it in info

	// Get buffer size
	procfs_buffer_size = len;
	if(procfs_buffer_size > MAX_LEN)
	{
		procfs_buffer_size = MAX_LEN;
	}
	
	// Write to buffer
	if(copy_from_user(procfs_buffer, buff, procfs_buffer_size))
	{
		return -EFAULT;
	}
	
	return procfs_buffer_size;
}

int read_info(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	//output the content of info to users buffer pointed by page
	int ret;

	if(off > 0)
	{
		ret = 0;
	}

	else
	{
		// fill buffer
		memcpy(page, procfs_buffer, procfs_buffer_size);
		ret = procfs_buffer_size;	
	}
	
	//len = sprintf(page, "%s\n", &info[read_index]);
	//read_index += len;
	return ret;
}

