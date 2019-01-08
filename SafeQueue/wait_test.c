#include <unistd.h>
#include "safe_queue.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

safe_queue *Q;
pthread_cond_t cond;		//阻塞
pthread_mutex_t mutex;		//锁

int exit_pop = 0;


void* handle_push(void *arg){	
	int i = 5;
	int id = *(int*)(arg);
	while(i > 0){
		int e = id * 100 + i;
		push_queue(Q, e);
		//唤醒 等待
		pthread_cond_signal(&cond);
		printf("push id[%d] i[%d] e[%d]\n", id, i, e);
		i--;
		sleep(id);
	}
	printf("push id[%d] is over!\n", id);
}

void* handle_pop(void *arg){
	int i = 10;
	int id = *(int*)(arg);
	while(i > 0){
		int e;
		pop_queue(Q, &e);
		if(e == -1){
			if(exit_pop == 1) break;
			printf("pop id[%d] i[%d] queue is null\n", id, i);
			if(pthread_mutex_lock(&mutex) == 0){
				printf("pop id[%d] wait!\n", id);
				//没事情可以挂起 等待
				pthread_cond_wait(&cond, &mutex);
				printf("pop id[%d] wait over!\n", id);
				pthread_mutex_unlock(&mutex);	
			}
		}
		printf("pop id[%d] i[%d] e[%d]\n", id, i, e);
		i--;
		sleep(1);
	}
	printf("pop id[%d] is over!\n", id);
}


int main(){
	Q = create_queue();
	init_queue(Q);
	pthread_t push_pid[5];		//5个放入队列的线程
	pthread_t pop_pid[5];		//3个消费队列的线程
	int param[5] = {1, 2, 3, 4, 5};
	if(pthread_mutex_init(&mutex, NULL)){
		exit(1);
	}	
	if(pthread_cond_init(&cond, NULL)){
		exit(1);
	}
	for(int i = 0; i < 5; ++i){
		if(pthread_create(&pop_pid[i], NULL, handle_pop, &param[i])){
			printf("Create thread failed\n");
			exit(1);
		}
	}	
	for(int i = 0; i < 3; ++i){
		if(pthread_create(&push_pid[i], NULL, handle_push, &param[i])){
			printf("Create thread failed\n");
			exit(1);
		}
	}	
	for(int i = 0; i < 3; ++i){
		pthread_join(push_pid[i], NULL);
	}
	exit_pop = 1;
	//避免等待 广播让pop线程退出
	pthread_cond_broadcast(&cond);

	for(int i = 0; i < 5; ++i){
		pthread_join(pop_pid[i], NULL);
	}
	release_queue(Q);
}
