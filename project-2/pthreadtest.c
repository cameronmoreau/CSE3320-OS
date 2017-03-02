#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 4

void *PrintHello(void *threadid) {
  long tid;
  tid = (long)threadid;

  printf("Hello world! its me, thread #%ld\n", tid);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  printf("hello world\n");
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  
  for(t = 0; t < NUM_THREADS; t++) {
    printf("Creating thread %ld\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
    if(rc) {
      printf("ERROR; return code from create is %d\n", rc);
      exit(-1);
    }
  }

  for(t = 0; t < NUM_THREADS; t++) {
    pthread_join(threads[t], NULL);
    printf("%d finished\n", t);
  }

  printf("MAIN FINISH\n");
  pthread_exit(NULL);
}