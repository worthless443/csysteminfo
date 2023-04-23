#include<string.h>
#include<stdlib.h>

#include<strutils.h>

int erase_portions(char *buffer, struct Ranges range) {
	int nl=0,range_start=0, range_end=0;
	const int old_size = strlen(buffer);
	for(int i=0;i<strlen(buffer);++i) {
		if(nl==range.s) range_start = i;
		else if(nl==range.e) range_end = i;
		if(*(buffer + i)=='\n') ++nl;
	}
	for(int i=range_start+1,ii=0;i<=range_end;++i,++ii)  {
		*(buffer + i) = *(buffer + range_end + ii + 1) ;
	}
	if(range.s == range.e - 1) {
		if(range.e == nl || range.e == nl - 1) {
			memset(buffer + range_end, '\0', range_end - range_start);
			return 0;
		}
		for(int i=1;i<=strlen(buffer) - range_end;++i)
			*(buffer + range_start + i) = *(buffer + range_end + i);
	}
	for(int i=1;i<=old_size - range_end;++i) {
		*(buffer + range_start + i) = *(buffer + range_end + i);
	}
	//memset(buffer + range_end, '\0', range_end - range_start);
	return 1; // TODO error check
}

int erase_blankNL(char *buffer) {
	int nl=0, asize=100;
	const int old_size = strlen(buffer);
	char _buf[asize], data[asize*10];
	memset(_buf,'\0',100);
	memset(data,'\0',asize*10);
	for(int i=0;i<strlen(buffer);++i) {
		if(*(buffer + i)=='\n') {
			memcpy(_buf,buffer + nl, i - nl);
			nl = i;
			if(strlen(_buf)>1) strcat(data,_buf);
			memset(_buf,'\0', i);
		}
	}
	strcat(buffer, data);
	/* always works method */
	//memcpy(buffer, data, strlen(data));
	//memset(buffer + strlen(data), '\0', strlen(buffer) - strlen(data));
	for(int i=0;i<strlen(buffer) - old_size;++i) 
		*(buffer + i) = *(buffer + old_size +  i);
	memset(buffer + old_size,'\0',(strlen(buffer) - old_size) + 2);
	return 0;
}
