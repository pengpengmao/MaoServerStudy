#include <stdio.h>

int merge(int a[], int s, int mid, int d)
{
	int i = s;
	int m = mid;
	int count = 0;
	while(s <= mid){
		int rt = a[s];
		int j = m + 1;
		while(j <= d){
			int lt = a[j];
			if(rt > lt) count++;
			j++;
		}
		s++;
	}	
	return count;
}


int merge_sort_count(int a[], int s, int d)
{
	if(s >= d) return 0;
	int mid = (s + d) /2;
	int rc = merge_sort_count(a, s, mid);
	int lc = merge_sort_count(a, mid + 1, d);
	int mc = merge(a, s, mid, d);
	return rc + lc + mc;
}


int get_count(int a[], int n)
{
	return merge_sort_count(a, 0, n - 1);
}

int main()
{
	int a[] = {2, 4, 3, 1, 5, 6};
	int s[] = {9, 8, 7, 6, 2, 4};
	int r = get_count(a, 6);
	printf("reversed_pair:%d\n", r);
	r = get_count(s, 6);
	printf("reversed_pair:%d\n", r);
	return 0;
}
