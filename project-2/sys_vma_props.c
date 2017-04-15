#include <linux/kernel.h>
#include <linux/sched.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <linux/mm_types.h>

asmlinkage int sys_vma_props(unsigned long mem, int pid)
{

	struct task_struct *task = find_task_by_vpid(pid);
	struct mm_struct *memory = task->active_mm;

	int data = 0;
	int ref = 0;
	int dirty = 0;

	pgd_t *pgd = pgd_offset(memory, mem);
	pud_t *pud = pud_offset(pgd,mem);
	pmd_t *pmd = pmd_offset(pud, mem);
	pte_t *ptep = pte_offset_kernel(pmd, mem);
	pte_t pte = *ptep;

	data = pte_present(pte);
	printk("Present flag: %i\n", data?1:0);
	ref = pte_young(pte);
	printk("Referenced flag: %i\n", ref?1:0);
	dirty = pte_dirty(pte);
	printk("Dirty flag: %i\n", dirty?1:0);

	return 0;
}

