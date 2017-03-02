#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024
#define NUM_THREADS 4

int total = 0;
int n1,n2;
char *s1,*s2;
FILE *fp;

struct worker_args {
  int start;
  int end;
  int total;
};

int readf(FILE *fp)
{
	if((fp=fopen("strings.txt", "r"))==NULL){
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}
	s1=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory!\n");
		return -1;
	}
	s2=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory\n");
		return -1;
	}
	/*read s1 s2 from the file*/
	s1=fgets(s1, MAX, fp);
	s2=fgets(s2, MAX, fp);
	n1=strlen(s1);  /*length of s1*/
	n2=strlen(s2)-1; /*length of s2*/
	if(s1==NULL || s2==NULL || n1<n2)  /*when error exit*/
		return -1;

  return 0;
}

void *num_substring_worker(void *worker_args) {
  int count, i, j, k;
  struct worker_args *args = (struct worker_args *)worker_args;
  args->total = 0;

  /* printf("Start: %d - End: %d: Result %d\n", args->start, args->end, args->total); */
  
  /* Loop though its partition and find num_substring for local */
  for (i = args->start; i <= args->end; i++){   
		count=0;

		for(j = i,k = 0; k < n2; j++,k++){  /*search for the next string of size of n2*/  
			if (*(s1+j)!=*(s2+k)) break;
			else count++;

			if(count==n2) args->total++;                    
		}
	}

  /* printf("got it, total was %d\n", args->total); */

  pthread_exit(NULL);
}

int num_substring() {
  pthread_t threads[NUM_THREADS];
  struct worker_args args[NUM_THREADS];

  int i,rc;
  int max = n1 - n2;

	int bsize = max / NUM_THREADS;
  int bleft = max % bsize;

  /* Initalize threads */
  for(i = 0; i < NUM_THREADS; i++) {
    /* Set struct to give the worker arguments */
    args[i].start = i * bsize;
    args[i].end = args[i].start + bsize;

    // Check if last, give left over
    if(i == NUM_THREADS - 1) {
      args[i].end += bleft;
    }

    /* Create the thread */
    rc = pthread_create(&threads[i], NULL, num_substring_worker, (void *)&(args[i]));
    if(rc) {
      printf("ERROR; return code from create is %d\n", rc);
      exit(-1);
    }
  }

  /* Wait for threads to finish - increment total */
  for(i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    total += args[i].total;
  }

  return total;
}

int main(int argc, char *argv[]) {
  int count;

  readf(fp);
	count = num_substring();
 	printf("The number of substrings is: %d\n", count);
  return 1;
}