#include<stdio.h>
#include<regex.h>
#include<string.h>
#include<stdlib.h>
#include<sys/sysinfo.h>

#define RE_MATCH 0

// parse the files as to get the number of the second from the column of info 
int memused(int *arr) {
	FILE *f = fopen("/proc/meminfo", "r");
	char buf[1];
	regex_t re, re1;
	int res;
	int c=0;
	char *out = malloc(sizeof(char) * 100);
	while(fread(buf,1,1,f)) {
	 	if((res=regcomp(&re, "[a-zA-Z\(\_\:]",REG_EXTENDED))==0) {
			int match = regexec(&re, buf,0,NULL,0);
			if(match==REG_NOMATCH) {
					if(buf[0]!=" "[0] && buf[0]!="\n"[0] ) {
						arr[++c-1] = atoi(buf);
					}
				}
			}
	} 
	for(int i=0;i<2;i++) { // cope fucking cope
	//	if((regcomp(&re1, "[0-9]", REG_EXTENDED)==0)) {
	//		if(regexec(&re,(char*)&out[i],0,NULL,0)==0) printf("%s\n",(char*)&out[i] );
	//	}
		printf("%s\n", (char*)&out[i]);
		
	}
	//printf("%s\n", out);
	free(out);
}

int topower(int val, int by) {
	int ret=1;
	for(int i=0;i<=by;i++) ret*=val;
	return ret;
}

int main() {
	struct sysinfo info;
	if(sysinfo(&info)<0) return -1;
	printf("says %ld\n",(info.freeram * info.mem_unit)/topower(10,9));
	int *arr = malloc(sizeof(int)*1000);
	char *out = malloc(sizeof(char)*1000);
	memused(arr);
	for(int i=8;i<15;i++) {
		char buf[1];
		sprintf(buf,"%d", arr[i]);
		strcat(out,buf);
	}
	int memused_i = atoi(out);
	printf("%d MiB free\n", memused_i/1000);
	free(arr);
	free(out);
	return 0;
}
