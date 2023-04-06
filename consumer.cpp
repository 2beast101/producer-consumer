#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>

key_t key;
const int THREAD_NUM = 1;

struct bufferSegment {
	int buffer[2];
	int index = 0;
	sem_t semEmpty, semFull;
	pthread_mutex_t mutexBuffer;
};
bufferSegment *p_mem;



void* consumer(void* args) {
	int y;
	
	while (1){

		sem_wait(&(p_mem->semFull));
		pthread_mutex_lock(&(p_mem->mutexBuffer));

		y = p_mem->buffer[p_mem->index-1];
		std::cout << "Consumed " << y << " at index " << p_mem->index-1 << std::endl;
		p_mem->index = p_mem->index-1;
		// consume
		pthread_mutex_unlock(&(p_mem->mutexBuffer));
		sem_post(&(p_mem->semEmpty));
		sleep(1);
	}
}


int main(int argv, char* argc[]){
	pthread_t th[THREAD_NUM];

	
	int shmid;
	int i;	
	key = ftok("/workspaces/producer-consumer", 9999999);

	shmid = shmget(key, sizeof(bufferSegment), IPC_CREAT | 0666);
	
	
	p_mem = (bufferSegment*)shmat(shmid, 0, 0);

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
	pthread_mutex_init(&(p_mem->mutexBuffer), NULL);
	sem_destroy(&(p_mem->semEmpty));
	sem_destroy(&(p_mem->semFull));
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
