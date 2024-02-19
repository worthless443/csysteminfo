#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

const char cmd[] = "upower -i /org/freedesktop/UPower/devices/battery_BAT0";

char *key2value(char **lines, int size, const char *ikey) {
	for(int a=0;a<size - 7;++a) {
		int i;
		char *line = lines[a];
		// TODO use realloc() instead of a static size 
		char *key = malloc(sizeof(char) * (1 << 6));
		char *value = malloc(sizeof(char) * (1 << 6));
		for(i=0;line[i] != ':';++i)
			key[i] = line[i];
		
		if(0 == strcmp(key,ikey)) {
			free(key);
			memcpy(value,line + i + 1, strlen(line) - i);
			return value;
		}
		free(key);
	}
	return NULL;
}

char *get_command_buffer(const char *key) {
	FILE *cf = popen(cmd, "r");
	char *buffer = malloc(sizeof(char));
	char *tmp = buffer;
	int size_buffer;
	int a = 0;
	for(int i=0;fread(buffer + i,1,1,cf);++i) {
		buffer = realloc(buffer, size_buffer=sizeof(char) *(i + 1) * 2);
	}
	char **lines = malloc(100 * sizeof(char*));
 	for(int i=0,b=-1,nl=0;i<size_buffer/sizeof(char);++i)	{
		if(nl == 0) {
			lines[a] = malloc(sizeof(char) * 2);
		}
		if(buffer[i] == '\n') {
			a++;
			b = -1;
			i+=1;	
			nl = 0;
		}
		else if(buffer[i] != ' ') {
			//printf("%c\n",buffer[i]);
			lines[a][++b]	= buffer[i];
			lines[a] = realloc(lines[a], sizeof(char) * (b + 1) * 2);
			nl++;
		}

	}
	
	free(buffer);
	return key2value(lines,a,key);
}

int main(int argc, char **argv) {
	char *key = NULL;
	if(argc < 2) 
		key = "capacity";
	else 
		key = argv[1];
	printf("%s\n", get_command_buffer(key));
}
