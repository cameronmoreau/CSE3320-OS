#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define __NR_report_process_virtual 339

void *runSystemCall(void *a) {
  int i = (int)a;
  printf("Running thread %i\n", i);
  syscall(__NR_report_process_virtual, i);
}

int main(int argc, char *argv[]) {
  printf("Test syscall - report process");
  int i = atoi(argv[1]);
  pthread_t t1, t2, t3;

  pthread_create(&t1, NULL, runSystemCall, (void *)i);
  pthread_create(&t2, NULL, runSystemCall, (void *)i);
  pthread_create(&t3, NULL, runSystemCall, (void *)i);

  pthread_exit(NULL);
  return 0;
}
