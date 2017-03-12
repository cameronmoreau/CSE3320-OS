#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define BUFFER 5

int m,n,end;
char *s1,*s2;
char buffer[BUFFER];


pthread_mutex_t mutex;
pthread_cond_t empty, full;

typedef struct strdata
{
	int tno;
	int tcount;

}strdata;

void producer(FILE *fp)
{
	char s1 = fgetc(fp);
	while(1)
	{
		pthread_mutex_lock(&mutex);
		buffer[m] = s1;
		m = (m + 1)%BUFFER;
		if((m - 1)%BUFFER == n)
		{
			pthread_cond_signal(&empty);
		}
		if(m == n)
		{
			pthread_cond_wait(&full, &mutex);
		}
		pthread_mutex_unlock(&mutex);

		s1 = fgetc(fp);
		if(feof(fp))
		{
			pthread_mutex_lock(&mutex);
			end = 1;
			pthread_cond_signal(&empty);
			pthread_mutex_unlock(&mutex);
			break;
		}
	}
}

void consumer(void *ptr)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(m == n)
		{
			if(end)
			{
				break;
			}
			else
			{
				pthread_cond_wait(&empty, &mutex);
				if(m == n && end)
				{
					break;
				}
			}
		}
		printf("%c", buffer[n]);
		n = (n + 1)%BUFFER;
		if(m == (n - 1)%BUFFER)
		{
			pthread_cond_signal(&full);
		}
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t pro,con;
	FILE *fp;

	m = 0;
	n = 0;

	if((fp=fopen("strings.txt","r"))==NULL)
	{
		printf("ERROR: Can't open file!\n");
		return -1;
	}

	/* Initialize  */
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&full, NULL);

	end = 0;

	
	/* Create  */
	pthread_create(&pro, NULL, (void *) &producer, (FILE *) fp);
	pthread_create(&con, NULL, (void *) &consumer, NULL);

	pthread_join(pro, NULL);
	pthread_join(con, NULL);

	/* Release  */
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&empty);
	pthread_cond_destroy(&full);
	
	return 1;
}








