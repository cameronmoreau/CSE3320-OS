#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_helloworld 337
#define __NR_print_self 338
#define __NR_print_other 339
#define __NR_vma_props 340

int main(int argc, char * argv[])
{
	int mem = atoi(argv[1]);
	int pid = atoi(argv[2]);
	
	//int pid = 2106; 
	//syscall(__NR_helloworld);
	//syscall(__NR_print_self);
	//syscall(__NR_print_other, pid);
	syscall(__NR_vma_props, mem, pid);
	return 0;
}
