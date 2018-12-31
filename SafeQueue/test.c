#include <unistd.h>
#include "safe_queue.h"
#include <stdio.h>
#include <pthread.h>

safe_queue *Q;

void* handle_push(void *arg){	
	int i = 10;
	int id = *(int*)(arg);
	while(i > 0){
		int e = id * 100 + i;
		push_queue(Q, e);
		printf("push id[%d] i[%d] e[%d]\n", id, i, e);
		i--;
		sleep(1);
	}
	printf("push id[%d] is over!\n", id);
}

void* handle_pop(void *arg){
	int i = 10;
	int id = *(int*)(arg);
	sleep(1);
	while(!is_empty_queue(Q)){

		int e;
		sleep(id);
		pop_queue(Q, &e);
		if(e == -1){
			printf("pop id[%d] i[%d] queue is null\n", id, i);
			break;
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
	pthread_t pop_pid[3];		//3个消费队列的线程
	int param[5] = {1, 2, 3, 4, 5};
	for(int i = 0; i < 5; ++i){
		if(pthread_create(&push_pid[i], NULL, handle_push, &param[i])){
			printf("Create thread failed\n");
			exit(1);
		}
	}	
	for(int i = 0; i < 3; ++i){
		if(pthread_create(&pop_pid[i], NULL, handle_pop, &param[i])){
			printf("Create thread failed\n");
			exit(1);
		}
	}	
	for(int i = 0; i < 5; ++i){
		pthread_join(push_pid[i], NULL);
	}
	for(int i = 0; i < 3; ++i){
		pthread_join(pop_pid[i], NULL);
	}
	release_queue(Q);
}
