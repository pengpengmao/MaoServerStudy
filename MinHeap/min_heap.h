#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include <stdio.h>

typedef struct min_heap{
	int len;
	int assign;
	int *a;
}min_heap;

min_heap * new_min_heap(){
	min_heap * mh = (min_heap* )malloc(sizeof(mh));
	mh->len = 0;
	mh->assign = 0;
	return mh;
}

void delete_min_heap(min_heap *mh){
	if(mh->a){
		free(mh->a);
	}
	free(mh);
	mh = NULL;
}

int is_empty_min_heap(min_heap *mh){
	return 0 == mh->len;
}

int get_min_heap_size(min_heap *mh){
	return mh->len;
}

int reserve_min_heap(min_heap *mh, unsigned n){
	if(mh->assign < n){
		unsigned assign = mh->assign ? mh->assign * 2 : 8;
		if(assign < n)
			assign = n;
		int *a;
		if(!(a = (int *)realloc(mh->a, assign * sizeof(int)))){
			return -1;
		}
		mh->a = a;
		mh->assign = assign;
	}	
	return 0;
}

void shift_down_min_heap(min_heap *mh, int index){
	if(mh->len <= 1) return ;
	int left_child = index * 2 + 1;
	if(left_child > mh->len){
		return ;
	}
	int min_child = left_child;
	int right_child = left_child + 1;
	if(right_child > mh->len){
		if(mh->a[index] > mh->a[min_child]){
			swap_array_value(mh->a, index, min_child);
		}
		return ;
	}
	if(mh->a[right_child] < mh->a[left_child]) min_child = right_child;
	swap_array_value(mh->a, index, min_child);
	shift_down_min_heap(mh, min_child);
}

int pop_min_heap(min_heap *mh){
	if(mh->len == 0) return -1;
	int e = mh->a[0];
	mh->a[0] = mh->a[--mh->len];
	shift_down_min_heap(mh, 0);
	return e;
}

void swap_array_value(int *a, int i, int j){
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void shift_up_min_heap(min_heap *mh, int index){
	if(index <= 0) return ;
	int father_index = (index - 1) / 2;
	//子节点小于 父节点
	if(mh->a[father_index] > mh->a[index]){
		int temp = mh->a[father_index];
		mh->a[father_index] = mh->a[index];
		mh->a[index] = temp;
		shift_up_min_heap(mh, father_index);
	}
}

int push_min_heap(min_heap *mh, int e){
	if(reserve_min_heap(mh, mh->len + 1)){
		return -1;
	}	
	mh->a[mh->len++] = e;
	shift_up_min_heap(mh, mh->len - 1);
	return 0;
}

void print_min_heap(min_heap *mh){
	printf("min_heap :\n");
	for(int i = 0; i < mh->len; ++i){
		printf("%d\t", mh->a[i]);
	}
	printf("\n");
}


#endif
