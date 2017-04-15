#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/fs.h>
#include <asm/page.h>
#include <asm/mman.h>

asmlinkage int sys_report_process_virtual(int pid) {
  
  struct task_struct *task;
  struct mm_struct *mem;
  struct vm_area_struct *vmalist;
  struct vm_area_struct vma;
  
  int vma_count = 0;
  unsigned long prot = 0;
  unsigned long start = 0;
  int count = 0;
  int size = 0;
  char *name;
  
  printk("==================\n");
  printk("Hello from process reporter!\n");
  printk("You want process %d\n", pid);
  
  /* Find task by its PID */
  task = pid_task(find_vpid(pid), PIDTYPE_PID);
  
  /* Check if task exists */
  if(task == NULL) {
    printk("Task with PID %d does not exist\n", pid);
    return 0;
  } 
  
  /* Use task to build mm */
  mem = task->active_mm;
  vmalist = mem->mmap;
  vma_count = mem->map_count;
  vma = *vmalist;
  
  start = vma.vm_start;
  
  printk("Found task with pid: %d\n", task->pid);
  
  /* Log size of virtual address space */
  printk("There are %i virtual memory areas\n", vma_count);
  for(vma = *vmalist; count < vma_count; count++) {
    prot = vma.vm_flags;
    
    printk("--------------------------\n");
    printk("VMA #%i\n", count + 1);
    printk("==> Start Addr 0x%lx\n", vma.vm_start);
    printk("==> End Addr 0x%lx\n", vma.vm_end);
    printk("==> Total Size: %lu\n", vma.vm_end - vma.vm_start);
    printk("==> Access Permission:\n");
    printk("Read Permission: %s\n", prot&PROT_READ ? "Yes": "No");
  } 
  
  return 1;
}
