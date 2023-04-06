#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/ipc.h>

key_t key;




const int THREAD_NUM = 2;

struct bufferSegment {
	int buffer[2];
	int index = 0;
	sem_t semEmpty, semFull;
	pthread_mutex_t mutexBuffer;
};


bufferSegment *p_mem;


void* producer(void* args) {
	



	while (1){
		int x = rand() % 100;

		sem_wait(&(p_mem->semEmpty));
		pthread_mutex_lock(&(p_mem->mutexBuffer));
		p_mem->buffer[p_mem->index] = x;


		std::cout << "Produced " << x << " at index " << p_mem->index << std::endl;
		p_mem->index = p_mem->index+1;
		
		pthread_mutex_unlock(&(p_mem->mutexBuffer));
		sem_post(&(p_mem->semFull));
		sleep(1);
	}
}


int main(int argv, char* argc[]){
	srand(time(NULL));
	pthread_t th[THREAD_NUM];
	key = ftok("/workspaces/producer-consumer", 9999999);

	int i;
	int shmid;

	shmid = shmget(key, sizeof(struct bufferSegment), IPC_CREAT | 0666); // ?

	p_mem = (bufferSegment*) shmat(shmid, 0, 0);
	pthread_mutex_init(&(p_mem->mutexBuffer), NULL);



	sem_init(&(p_mem->semEmpty), 1, 2); // initialize semEmpty,  with value 2, as there are 2 empty slots
	sem_init(&(p_mem->semFull), 1, 0); // intialize semFull, with 0, as there are 0 full slots



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
	


	pthread_mutex_init(&(p_mem->mutexBuffer), NULL);
	sem_destroy(&(p_mem->semEmpty));
	sem_destroy(&(p_mem->semFull));
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}