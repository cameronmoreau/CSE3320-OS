#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_report_process_virtual 339

int main(int argc, char *argv[]) {
  printf("Test syscall - report process");
  int i = atoi(argv[1]);

  syscall(__NR_report_process_virtual, i);
  return 0;
} 
