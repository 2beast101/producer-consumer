#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int buffer[2];
int count = 0;

const int THREAD_NUM = 2;
pthread_mutex_t mutexBuffer;

sem_t semEmpty, semFull;

void* producer(void* args) {
	while (1){
		int x = rand() % 100;
		sleep(1);
		sem_wait(&semEmpty);
		pthread_mutex_lock(&mutexBuffer);
		
		buffer[count] = x;
		count++;
		
		
		pthread_mutex_unlock(&mutexBuffer);
		sem_post(&semFull);
	}
}


void* consumer(void* args) {
	// Remove from buffer
	while (1){
		int y ;
		sem_wait(&semFull);
		pthread_mutex_lock(&mutexBuffer);
		
		
		y = buffer[count - 1];
		count--;
		

		

		// consume
		std::cout << "Got " << y << std::endl;
		// sleep(1);
		pthread_mutex_unlock(&mutexBuffer);
		sem_post(&semEmpty);

	}
	
	
}


int main(int argv, char* argc[]){
	srand(time(NULL));
	pthread_t th[THREAD_NUM];
	pthread_mutex_init(&mutexBuffer, NULL);
	sem_init(&semEmpty, 0, 2);
	sem_init(&semFull, 0, 0);
	int i;
	for (i = 0; i < THREAD_NUM; ++i ) {
		if (i % 2 == 0) {
			if (pthread_create(&th[i], NULL, &producer, NULL) != 0) {
				perror("Failed to create thread");
			}
		} else {
			if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
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
