#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

asmlinkage int sys_print_self(void) {
	/* Macro for current running process */
	struct task_struct *task = current;

	printk("Process ID: %d\n", task->pid);
	printk("Running State: %ld\n", task->state);
	printk("Program Name: %s\n", task->comm);
	printk("Start Time: %llx\n", task->se.exec_start);
	printk("Virtual Runtime: %llx\n", task->se.vruntime);

	printk("\nPARENT PROCESSES:\n");
	
	for(task = task->parent; task != &init_task; task=task->parent) {
		printk("\t%s [%d] - %ld\n", task->comm, task->pid, task->state);
	}
	return 1;
}
