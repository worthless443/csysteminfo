#include<stdio.h>
#include<regex.h>
#include<string.h>
#include<stdlib.h>
#include<sys/sysinfo.h>


int memused() {
	FILE *f = fopen("/proc/meminfo", "r");
	char buf[1];
	regex_t re;
	int res;
	int c=0;
	char *out = malloc(sizeof(char) * 10);
	while(fread(buf,1,1,f)) {
	 	if((res=regcomp(&re, "[a-zA-Z\(\_\:]",REG_EXTENDED))==0) {
			int match = regexec(&re, buf,0,NULL,0);
			if(match==REG_NOMATCH) {
				if(++c<8) {
					if(buf[0]!=" "[0] && buf[0]!="\n"[0] )
						out[c-1]  = buf[0];
				}
				else {
					c = 0;
					printf("%s\n", out);
					for(int i=0;i<8;i++) out[i] = 0;
				}
			}
}

	} 
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
	printf("%ld\n",(info.freeram * info.mem_unit)/topower(10,9));
	memused();
}
