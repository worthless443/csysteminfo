#include<stdio.h>

void print_arr(int *arr, int size) {
	for(int i=0;i<size;++i) 
		printf("%d ", arr[i]);
	printf("\n");
}

static int match_arr(int *a1, int *a2,int size) {
	int match = 0;
	for(int i=0;i<size;++i)
		if(a1[i] != a2[i] ) ++match;
	return match;
}

int sort_int(int *arr, int size, int big) {
	int repl[size];
	do {
		for(int i=0;i<size;++i)
			repl[i] = arr[i];
		for(int i=0;i<size-1;i+=1) {
			if(big) {
				if(arr[i]<arr[i+1]) {
					int tmp = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = tmp;
				}
			}
			else if(!big) {
				if(arr[i]>arr[i+1]) {
					int tmp = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = tmp;
				}
			}
		}
		if(match_arr(arr,repl,size) == 0) break;
	} while(1);
	return 0;
}
