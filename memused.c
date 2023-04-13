#include<stdio.h>
#include<regex.h>
#include<string.h>
#include<stdlib.h>
#include<sys/sysinfo.h>

#include<strutils.h>

#define RE_MATCH 0

// parse the files as to get the number of the second from the column of info 
static int memused(int *arr) {
	FILE *f = fopen("/proc/meminfo", "r");
	char buf[1];
	regex_t re;
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
		regfree(&re);
	} 
	fclose(f);
	free(out);
	return 1; // TODO do error check 
}


static int topower(int val, int by) {
	int ret=1;
	for(int i=0;i<=by;i++) ret*=val;
	return ret;
}
static size_t sysinfo_ram() {
	struct sysinfo info;
	if(sysinfo(&info)<0) return -1;
	return info.freeram * info.mem_unit/topower(10,9);
}
// TODO write test cases for range and string
const char *buffer = "fuck\nyou\nfucking\n\nnigger\ncoomer\n\nsoyjack\n";

static char *filter_nonint(const char *str) {
	char *out = malloc(sizeof(char)*100);
	for(int i = 0,j=-1;i<strlen(str);++i)
		if(*(str + i)>='0' && *(str + i) <='9')
			out[++j] = str[i];
	return out;
}

static int test_strutils(const char *buffer, struct Ranges range) {
	char *m_buffer = malloc(sizeof(char)*1000);
	memcpy(m_buffer, buffer, strlen(buffer));
	erase_blankNL(m_buffer);
	erase_portions(m_buffer, range);
	printf("%s",m_buffer);
	free(m_buffer);
	return 1;
}
int memused_wrapper() {
	int *arr = malloc(sizeof(int)*1000);
	char *out = malloc(sizeof(char)*1000),*snum = NULL;
	memused(arr);
	for(int i=8;i<15;i++) {
		// use two
		char buf[2];
		sprintf(buf,"%d", arr[i]);
		strcat(out,buf);
	}
	snum = filter_nonint((const char*)out);
	int memused_i = atoi(snum);
	free(arr);
	free(out);
	free(snum);
	return memused_i/1000;
}
#ifndef __MAIN__
void unused_functions() {
	struct Ranges range = {1,2};
	(void)sysinfo_ram();
	test_strutils((char*)NULL,range);
}
#endif
#ifdef __MAIN__
int main() {
	memused_wrapper()
}
#endif
