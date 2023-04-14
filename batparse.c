#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

#include<xtoi.h>
#ifdef _USE_CONFIG_F
#include<config.h>
#endif

#ifdef __DEBUG_PRINT_3
#define __DEBUG_PRINT_2 // TODO find things to add for this flag
#define __DEBUG_PRINT_1
#endif

#ifdef __DEBUG_PRINT_2
#define __DEBUG_PRINT_1
#endif


// these two functions help with positions of the string to be parsed
static int getNLnumber(const char *str, int stpcnd) {
	int size = 0,d=0;
	for(int i=0;d<=stpcnd-1;) { 
		int x = i, y = size;
		++i;
		if(str[i]==*"\n") ++size; 
		if(!(size - y) - (i - x)) ++d;
		else d=0;
	}
	return size - d;
}

static int getNLuntil(const char *str, int ascii) {
	int times=0;
	for(int i=0;*(str + i)!=ascii;i++) {
		if(*(str + i)==*"\n") times++;
	}
	return times;
}

static int getNLwhole(const char *str, int ascii) {
	int times;
	for(times=0;*(str + times)!=ascii;++times);
	return times;
}

#ifdef __DEBUG_SYMBOLS
int getNLwholeChar(const char *str, const char *mat) {
#else
static int getNLwholeChar(const char *str, const char *mat) {
#endif
	int times=0,i;
	for(i=0;i<strlen(str);i++)  {
		for(int j=0;j<strlen(mat);++j) {
			if(str[i+j]==mat[j]) times++;
			else  times=0;
		}
		if(times>=strlen(mat)) break;
	}
	(void)getNLuntil; // git rid of warning for now
	return i;
}

static int reachRelvBuf1(const char *str, char *buf) {
	int times = 0, content=0;
	int chr = '\n';
	char buffer_[100];
	char pert[10];
	char charge[10];
	memcpy(buf,str,getNLwholeChar(str, "ing"));
#ifdef __DEBUG_PRINT_3
	printf("debug2: %s\n", buf);
#endif
	for(int i=0;i<2;++i) strcat(buf, (char*)&chr);
	for(int i=0,ii=-1;i<strlen(buf);++i) {
		if(*(buf+i)=='\n') times++;
		if(times>=getNLnumber(buf,2)) buffer_[++ii] = buf[i];
	}
	for(int i=0,ii=-1;i<strlen(buffer_);++i) 
		if(*(buffer_ + i)!=' ') pert[++ii] = buffer_[i];
	for(int nl=0;content<strlen(pert);++content) {
		if(*(pert + content)=='\n') nl++;
		if(nl==2) break;
	}
	memset(pert + content, '\0', strlen(pert) - content);
	for(int i=0;i<strlen(pert + 1);++i) 
		if(*(pert + i + 1)==':') {
				memcpy(charge, pert + i + 1, strlen(pert + 1) - i)	;
		}
	memset(charge + strlen("charg") + 1, '\0', strlen(charge) - strlen("charg") + 1);
#ifdef __DEBUG_PRINT_1
	printf("debug2: %s\n", charge);
#endif
	if(strcmp(charge + 1,"charg")==0) return 1; // matching against discharge buggy with buffers and addresses
	else return 0;
	return -1;
}

static int getNLcount(const char *buffer) {
	int nl_i=0;
	for(int nl=0;nl_i<strlen(buffer);++nl_i) {
		if(*(buffer + nl_i)=='\n') ++nl;
		if(nl>1) break;
	}
	return nl_i;
}
static int insertNL(char *buffer) {
	for(int i=0;i<4;++i) 
		*(buffer + strlen(buffer)) = '\n';
	return 1;
}
static int reachRelvBuf(const char *str, char *buf) {
	int size=0,times=0,nl_i;
	char buffer[100];
	for(int i=0;;size++) {
		if(*(str+size)==*"\n") times++;
		if(times>=getNLnumber(str, 2)) {
			*(buf+i) = str[size];
			i++;
		}
		if(*(str+size)=='%') break;
	}
	for(int i=0,ii=0;i<strlen(buf);i++) {
		if(buf[i]!='\n') {
			buffer[ii] = buf[i];
			++ii;
		}
	}
#ifdef __DEBUG_PRINT_3
	printf("debug3: %s\n", buffer);
#endif
	insertNL(buffer);
	const int old_size = strlen(buffer);
	memset(buffer + old_size + 2, '\0', 10);
	nl_i = getNLcount(buffer);
	memset(buffer + nl_i, '\0', strlen(buffer) - nl_i);
	memset(buffer + strlen(buffer) - 2, '\0', 1);
	insertNL(buffer);
	nl_i = getNLcount(buffer);
	memset(buffer + nl_i, '\0', strlen(buffer) - nl_i);
	memset(buf, '\0', strlen(buf));
    memcpy(buf, buffer, strlen(buffer));
#ifdef __DEBUG_PRINT_1
	printf("debug69:%s", buf);
#endif
	return 1; // TODO enable error checking associated with ret int
}
static int reachRelvNum(const char *str, char *buf) {
	for(int i=0,ii=0;i<strlen(str);i++) {
		if(str[i] >= '0' && str[i] <= '9') {
			buf[ii] = str[i];
			++ii;
		}
	}
	return 1; // TODO enable error checking associated with ret int
}

int parse_str(const char *str, char *buf) {
	size_t oldsize;
	char buffer_[100],buf_[1000];
	char buffer[100];
	memset(buf_,'\0',1000);
	memset(buffer,'\0', 100);
	memcpy(buf,str,getNLwhole(str, *"\%")+2);
	for(oldsize = 0;buf[oldsize] != '%';++oldsize);
	for(int i=0;i<4;i++) strcat(buf, "\n");
	memcpy(buf_,buf,++oldsize);
	//for(int i=0;i<strlen(buf);++i) {
	//	char test = buf[i];
	//	if(i>oldsize) {
	//		if(test == '\n')
	//			printf(&test);
	//	}
	//	else if(i == oldsize) printf("here");
	//	else
	//		printf(&test);
	//}
 	for(int i=oldsize,ii=oldsize-1;i<strlen(buf);++i)
 		if(buf[i]=='\n')
 			buf_[++ii] = buf[i];
	reachRelvBuf(buf_,buffer_);
	reachRelvNum(buffer_,buffer);
	memset(buffer + 4, '\0', 100 - 4);
#ifdef __DEBUG_PRINT_2
	printf("debug4: %s\n", buffer);
#endif
	return _atoi(buffer);
}
int parse_charge(const char *str, char *buf) {
	return reachRelvBuf1(str, buf);
}
