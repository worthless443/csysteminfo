#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
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

static int reachRelvBuf1(const char *str, char *buf, char *buffer_) {
	int times = 0, content=0,ii=-1;
	int chr = '\n';
	//char *buffer_ = malloc(sizeof(char)*1000);
	char *charge = malloc(sizeof(char*)*400);
	//char buf[strlen(tmpbuf) + 1];// = malloc(sizeof(char)*strlen(tmpbuf));
	//memset(buf,'\0',strlen(tmpbuf));
	//memcpy(buf,tmpbuf,strlen(tmpbuf));
	memcpy(buf,str,getNLwholeChar(str, "ing"));
#ifdef __DEBUG_PRINT_3
	printf("debug2: %s\n", buf);
#endif
	
	int old_size = strlen(buf);
	for(int i=1;i<=2;++i) buf[old_size + i] = chr;
	for(int i=0,ii=-1;i<strlen(buf);++i) {
		if(*(buf+i)=='\n') times++;
		if(times>=getNLnumber(buf,2)) buffer_[++ii] = buf[i];
		if(i == strlen(buf) - 1)
			buffer_[ii + 1] = 0;
	}

	for(int i=0;i<strlen(buffer_);++i)  {
		if(*(buffer_ + i)!=' ') ++ii;
	}
	char *pert = malloc(sizeof(char)*(ii*2));
	ii = -1;
	for(int i=0;i<strlen(buffer_);++i) {
		if(*(buffer_ + i)!=' ') {
			pert[++ii] = buffer_[i];
			if(i == strlen(buffer_) - 1)
				memcpy(pert + ii + 1, "\0\0",2);
			//printf("%d\n",ii);
		}
	}

	for(int nl=0;content<strlen(pert);++content) {
		if(*(pert + content)=='\n') nl++;
		if(nl==2) break;
	}
	memset(pert + content, '\0', strlen(pert) - content);
	for(int i=0;i<=strlen(pert + 1);++i) {
		if(*(pert + i + 1)==':') {
			memcpy(charge, pert + i + 1, strlen(pert + 1) - i)	;
			charge[(strlen(pert + 1) - i) + 1] = '\0';
			// wasteful: 
		}
		//printf("len %s\n", *charge);
	}
	memset(charge + strlen("charg") + 1, '\0', strlen(charge) - strlen("charg") + 1);
//#ifdef __DEBUG_PRINT_1
	printf("debug2: %s\n", charge);
//#endif
	free(pert);
	if(strcmp(charge + 1,"charg")==0) {
		free(charge);
		return 1; // matching against discharge buggy with buffers and addresses
	}
	else {
		free(charge);
		return 0;
	}
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

int old_strpd_char_len = 0;
int parse_str(const char *str, char *buf) {
	char buffer_[1000] = {0};
	char buffer[1000] = {0};
	char buf_[1000] = {0};
	int oldsize;
	int nl_whole = getNLwhole(str, '%');

	//memset(buf_,'\0',1000);
	//memset(buffer,'\0', 100);
	
	// BUG buffer keep getting larger : fixed

	memcpy(buf,str,nl_whole+2);
	for(oldsize = 0;buf[oldsize] != '%';++oldsize);
	
	memcpy(buf + nl_whole + 2, "\n\n\n\n",4);

	if(!old_strpd_char_len)
		old_strpd_char_len = strlen(buf);

	int change_offset = strlen(buf) - old_strpd_char_len ;
	
	assert(change_offset >= -10 && change_offset <= 10);
	old_strpd_char_len = strlen(buf);

	memcpy(buf_,buf,++oldsize);
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
	char *buffer_ = malloc(sizeof(char)*200);
	*buffer_ = 0;
	int ret = reachRelvBuf1(str, buf,buffer_);
	free(buffer_);
	return ret;
}
