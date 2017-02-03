#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

asmlinkage int sys_print_other(int inputPID)
{

    struct task_struct *task;
  
    /* Find task by PID */
    task = pid_task(find_vpid(inputPID), PIDTYPE_PID);
  
    /* Check for NULL */
    if (task == NULL)
    {
	return 0;
    }
    
    /* Print information for task */
    printk("Process ID: %d\n", task->pid);
    printk("Running State: %ld\n", task->state);
    printk("Program Name: %s\n", task->comm);
    printk("Start Time: %llx\n", task->se.exec_start);
    printk("Virtual Runtime: %llx\n", task->se.vruntime);

    printk("\nPARENT PROCESSES:\n");
	
    for(task = task->parent; task != &init_task; task=task->parent) 
    {
	printk("\t%s [%d] - %ld\n", task->comm, task->pid, task->state);
    }
 
    return 1;
}
