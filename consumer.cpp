#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>

int buffer[2];
int count = 0;

const int THREAD_NUM = 2;
pthread_mutex_t mutexBuffer;
sem_t semEmpty, semFull;

struct BufferSegment {
	int buffer[2];
	int index = 0;
};




void* consumer(void* args) {
	int item;
	BufferSegment *sharedBuff = (BufferSegment*)args;


	// Remove from buffer
	while (1){
		
		sem_wait(&semFull);
		pthread_mutex_lock(&mutexBuffer);

	// ?
		// consume
		pthread_mutex_unlock(&mutexBuffer);
		sem_post(&semEmpty);
		sleep(1);

	}
}


int main(int argv, char* argc[]){
	pthread_t th[THREAD_NUM];
	pthread_mutex_init(&mutexBuffer, NULL);

	sem_init(&semEmpty, 0, 2); // initialize semEmpty,  with value 2, as there are 2 empty slots
	sem_init(&semFull, 0, 0); // intialize semFull, with 0, as there are 0 full slots

	int i;
	shm_get(); // ?
	for (i = 0; i < THREAD_NUM; ++i ) {
		if (i % 2 == 0) {
			if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) { // Makes sure consumer thread is created correctly
				perror("Failed to create thread");
			}
		}
	}
	for (i = 0; i < THREAD_NUM; ++i ) {
		if (pthread_join(th[i], NULL) != 0) {
			perror("Failed to join thread");
		}
	}
	pthread_mutex_init(&mutexBuffer, NULL);
	sem_destroy(&semEmpty);
	sem_destroy(&semFull);
	return 0;
}
