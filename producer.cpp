#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>

const int KEY = 9999;

// int buffer[2];
int count = 0;

const int THREAD_NUM = 2;
pthread_mutex_t mutexBuffer;
sem_t semEmpty, semFull;

struct bufferSegment {
	int buffer[2];
	int index = 0;
};

bufferSegment *sharedBuff;


void* producer(void* args) {

	while (1){
		int x = rand() % 100;
		sem_wait(&semEmpty);
		pthread_mutex_lock(&mutexBuffer);
		
		
		pthread_mutex_unlock(&mutexBuffer);
		sem_post(&semFull);
	}
}


int main(int argv, char* argc[]){
	pthread_t th[THREAD_NUM];
	pthread_mutex_init(&mutexBuffer, NULL);

	sem_init(&semEmpty, 0, 2); // initialize semEmpty,  with value 2, as there are 2 empty slots
	sem_init(&semFull, 0, 0); // intialize semFull, with 0, as there are 0 full slots

	int i;
	int shmid;
	shmid = shmget(KEY, sizeof(bufferSegment), IPC_CREAT | 0775); // ?



	for (i = 0; i < THREAD_NUM; ++i ) {
		if (i % 2 == 0) {
			if (pthread_create(&th[i], NULL, &producer, NULL) != 0) { // Makes sure producer thread is created correctly
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
