#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
struct strpostion {
	int start,end;
};
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
	int times=0,i;
	for(i=0;*(str + i)!=ascii;i++);
	return i;
}

static int getNLwholeChar(const char *str, const char *mat) {
	int times=0,i;
	for(i=0;i<strlen(str);i++)  {
		for(int j=0;j<strlen(mat);++j) {
			if(str[i+j]==mat[j]) times++;
			else  times=0;
		}
		if(times>=strlen(mat)) break;
	}
	return i;
}

static void cleanbuf(char *buf) {

	char buffer_[100];
	//for(int i=0;fds);

}
static int reachRelvBuf1(const char *str, char *buf) {
	int times = 0;
	char buffer_[100];
	char buffer[100];
	char charge[30];
	memcpy(buf,str,getNLwholeChar(str, "ing"));
	for(int i=0;i<2;i++) *(buf + strlen(buf) + i) = '\n';
	for(int i=0;i<1;i++) *(buf + strlen(buf) + i) = '\n';
	for(int i=0,ii=-1;i<strlen(buf);++i) {
		if(*(buf+i)=='\n') times++;
		if(times>=getNLnumber(buf,2)) buffer_[++ii] = buf[i];
	}
	for(int i=0,ii=-1;i<strlen(buffer_);++i) 
		if(*(buffer_+i)!='\n') buffer[++ii] = buffer_[i];
	for(int i=0,ii=-1,state=0;i<strlen(buffer);i++) {
		if(*(buffer+i)==':') {
			state=1;
			++i;
		}
		if(state) if(*(buffer+i)!=' ') charge[++ii] = buffer[i];
	}
	printf("%s\n", charge);
	if(strcmp(charge,"charg")==0) return 1; // matching against discharge buggy with buffers and addresses
	else return 0;
	return -1;
}

static int reachRelvBuf(const char *str, char *buf) {
	int size,times=0;
	char buffer[100];
	for(int i=0,size=0;;size++) {
		if(*(str+size)==*"\n") times++;
		if(times>=getNLnumber(str, 2)) {
			*(buf+i) = str[size];
			i++;
		}
		if(*(str+size)==*"\%") break;
	}
	for(int i=0,ii=0;i<strlen(buf);i++) {
		if(buf[i]!='\n') {
			buffer[ii] = buf[i];
			++ii;
		}
	}
	for(int i=0;i<4;i++) *(buffer + strlen(buffer) + i) = '\n';
	for(int i=0;i<strlen(buf);i++) buf[i] = 0; // could be allowed with realloc()?
        memcpy(buf, buffer, strlen(buffer));

}
static int reachRelvNum(const char *str, char *buf) {
	for(int i=0,ii=0;i<strlen(str);i++) {
		if(str[i] > 48 && str[i] < 57) {
			buf[ii] = str[i];
			++ii;
		}
	}
}

int parse_str(const char *str, char *buf) {
	char buffer_[100];
	char buffer[3];
	memcpy(buf,str,getNLwhole(str, *"\%")+2);
	for(int i=0;i<4;i++) *(buf + (strlen(buf) + i)) = *"\n";
	reachRelvBuf(buf,buffer_);
	reachRelvNum(buffer_,buffer);
	return atoi(buffer);
}
int parse_charge(const char *str, char *buf) {
	return reachRelvBuf1(str, buf);
}
