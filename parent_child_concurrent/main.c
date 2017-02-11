#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NR_THREAD 2

int sum=0;
unsigned int seed;

void* func0(void *param) {
	int tmp;
	int i;
	for(i=0; i<10; i++) {
		tmp=sum;
		tmp++;
		if(rand_r(&seed)%2) {
			printf("sleeping for 1 sec\n");
			sleep(1);
		} else {
			printf("sleeping for 2 sec\n");
			sleep(2);
		}
		sum=tmp;
		if(rand_r(&seed)%2) {
			printf("sleeping for 1 sec\n");
			sleep(1);
		} else {
			printf("sleeping for 2 sec\n");
			sleep(2);
		}
	}

	return (void*)0;
}

int main() {
	int i;
	int error;
	pthread_t *tid;
	pthread_attr_t attr;

	seed=(unsigned int)time(NULL);

	if((tid=(pthread_t*)calloc(NR_THREAD, sizeof(pthread_t)))==NULL) {
		fprintf(stderr, "calloc() failed\n");
		exit(1);
	}

	pthread_attr_init(&attr);
	for(i=0; i<NR_THREAD; i++) {
		if((error=pthread_create(&tid[i], &attr, func0,
			(void*)0))) {
			fprintf(stderr, "pthread_create() failed: %d %d\n",
				i, error);
			tid[i]=pthread_self();
		}
	}

	for(i=0; i<NR_THREAD; i++) {
		if(pthread_equal(pthread_self(), tid[i]))
			continue;

		if((error = pthread_join(tid[i], NULL))) {
			fprintf(stderr, "pthread_join() failed: %d %d\n",
				i, error);
		}
	}

	printf("Final sum= %d\n", sum);

	free(tid);

	return 0;
}
