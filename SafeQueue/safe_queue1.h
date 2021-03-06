#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_QUEUE_LEN 128	//队列长度

typedef struct{
	int head;
	int tail;
	int cap;
	pthread_mutex_t lock;
	int *queue;
}safe_queue;

safe_queue* create_queue(){
	safe_queue *q = malloc(sizeof(safe_queue));
	q->tail = q->head = 0;
	q->cap = MAX_QUEUE_LEN;
	q->queue = malloc(sizeof(int) * q->cap);
}

void init_queue(safe_queue *q){
	pthread_mutex_init(&q->lock, NULL);
}

void expand_queue(safe_queue *q){
	q->cap = q->cap * 2;
	int *queue = realloc(q->queue, q->cap);
	q->queue = queue;
}

void push_queue(safe_queue *q, int e){
	pthread_mutex_lock(&q->lock);
	q->queue[q->tail++] = e;
	if(q->tail >= q->cap){
		q->tail = 0;
	}
	if(q->tail == q->head){
		expand_queue(q);
	}
	pthread_mutex_unlock(&q->lock);
}

void pop_queue(safe_queue *q, int* pe){
	pthread_mutex_lock(&q->lock);
	if(q->head == q->tail){
		pe = NULL;
		pthread_mutex_unlock(&q->lock);
		return ;
	}
	*pe = q->queue[q->head++];
	if(q->head >= q->cap){
		head = 0;
	}
	pthread_mutex_unlock(&q->lock);
}

int is_empty_queue(safe_queue *q){
	if(q->head == q->tail){
		return 1;
	}
	return 0;
}

void release_queue(safe_queue *q){
	free(q->queue)
	pthread_mutex_destroy(&q->lock);
	free(q);
}

