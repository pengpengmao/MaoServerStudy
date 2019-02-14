#include <stdio.h>
#include "min_heap.h"

int main()
{
	min_heap* mh = new_min_heap();
	int a[] = {8, 1, 3, 9, 12, 3, 2};
	printf("push min_heap\n");
	for(int i = 0; i < 7; ++i){
		push_min_heap(mh, a[i]);
		print_min_heap(mh);
	}
	printf("pop min_heap\n");
	for(int i = 0; i < 7; ++i){	
		printf("pop : %d \n", pop_min_heap(mh));
		print_min_heap(mh);
	}
	return 0;
}
