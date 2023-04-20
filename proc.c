#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<utils.h>

char *stdout_getcmd(const char *cmd) {
	char *data = malloc(sizeof(char));
	char *buf = data;
	FILE *f = popen(cmd,"r");
	for(int i=1;fread(buf,1,1,f);++i) {
		data = realloc(data, sizeof(char)*i);
		buf = data + (i - 1);
	}
	fclose(f);
	return data;
}

int calc_newline(char *buffer) {
	int nl=0;
	for(int i=0;i<strlen(buffer);++i)
		if(buffer[i]=='\n') ++nl;
	return nl;
}
int calc_line_size(char *buffer,int line) {
	if(line > calc_newline(buffer)) return -1;
	for(int i=0,ii=0,nl=-1;i<strlen(buffer);++i,++ii) {
		if(buffer[i] == '\n') ++nl;
		if(nl == line) return ii;
		if(buffer[i] == '\n') ii =0;
	}
	return 0;	
}

char **split_ps_buffer(char *buffer) {
	int nl_size = calc_newline(buffer); 
	int sizes[nl_size];//= malloc(sizeof(int)*nl_size);
	for(int i=0;i<nl_size;++i)
		sizes[i] = calc_line_size(buffer,i);
	sort_int(sizes,nl_size - 1,1);
	char **lines = malloc(sizeof(long long) *nl_size +1);
	for(int i=0,j=0,n=0;i<strlen(buffer);++i) {
		if(!n) {
			*(lines + j) = malloc(sizeof(char)* (*sizes * 3));
			memset(*(lines + j), '\0', *sizes * 3);
			n = 1;
		}
		char tmp = buffer[i];
		strcat(lines[j],&tmp);
		if(buffer[i] == '\n') {
			++j;
			n = 0;
		}
	}
	return lines;
}

void split_buffer_free(char **split_arr,int nl_size) {
	for(int i=0;i<nl_size;++i)
		free(split_arr[i]);
	free(split_arr);
}
void proc_free(char **split_arr,int nl_size) {
	for(int i=1;i<nl_size;++i)
		free(split_arr[i]);
	free(split_arr);
}


void make_it_parsable(char **split_arr, int nl_size) {
	for(int i=0;i<nl_size;++i) {
		int n = 0;
		for(int j=0;j<strlen(split_arr[i]);++j) {
			char *line = split_arr[i];
			if(line[j] == ' ' && !n) {
				line[j] = '|';
				n = 1;
			}
			else if(line[j] == ' ' && n) line[j] = '@';
			else if(line[j] != ' ' && n) n = 0;
		}
	}
}

char **get_processes(char **split_arr, int nl_size) {
	make_it_parsable(split_arr,nl_size);
	char **proc = malloc(sizeof(char)*nl_size + 1);
	for(int j = 1;j<nl_size;++j) {
		char *line = split_arr[j];
		int i = 0;
		for(int delim=0;i<strlen(line);++i) {
			if(line[i] == '|') 
				delim++;
			
			if(delim == 4) break;
		}
		proc[j] = malloc(sizeof(char)*100);
		memset(proc[j],'\0',100);
		memcpy(proc[j],line + i + 1,strlen(line + i + 1));
		memset(proc[j] + strlen(line + i -1),'\0',100 -strlen(line + i + 1));
	}
	return proc;
}

char *filter_nl(char *proc) {
	char *new = malloc(sizeof(char)*strlen(proc));
	memset(new,'\0',strlen(proc));
	for(int i=0,j=-1;i<strlen(proc);++i)
		if(proc[i] != '\n')
			new[++j] = proc[i];
	return new;
}

void print_process(char **procs,int nl_size,int offset) {
	printf("(");
	for(int i=offset;i<nl_size;++i) {
		char *new = filter_nl(procs[i]);
		printf((i < nl_size -1) ? "%s, " : "%s", new);
		free(new);
	}
	printf(")\n");
}

#ifdef __MAIN__
int main() {
	char *cmd = stdout_getcmd("ps -a");
	int nl_size = calc_newline(cmd);
	char **lines = split_ps_buffer(cmd);
	char **procs = get_processes(lines,nl_size);	
	print_process(procs,nl_size);
	split_buffer_free(lines,nl_size);
	proc_free(procs,nl_size);
	free(cmd);
}
#endif
