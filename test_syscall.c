#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_helloworld 337
#define __NR_print_self 338
#define __NR_print_other 339

int main(int argc, char * argv[])
{

  /* This will need to be changed as it is a pid taken from my laptop */
  int pid = 2106;
  
  syscall(__NR_helloworld);
  syscall(__NR_print_self);
  syscall(__NR_print_other, pid);
  return 0;
  
}
