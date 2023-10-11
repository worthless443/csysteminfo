#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include<batparse.h>
#include<proc.h>

int __calc_newline(char *cmd, int size) {
	int nl = 0;
	for(int i = 0;i<size - 1;++i)  {
		if(cmd[i] == '\n') ++nl;
		if(cmd[i] == 'p' && cmd[i + 1]=='s') break;
	}
		
	return nl;
}

int __calc_newline_buffer(char *cmd) {
	int nl = 0,i;
	for(i = 0;i<strlen(cmd) - 1;++i)  {
		if(cmd[i] == '\n') ++nl;
		if(cmd[i] == 'p' && cmd[i + 1]=='s') break;
	}
		
	return i + 2;
}

char *read_file(const char *cmd, const char *file) {
	int ret = system(cmd);
	int i;
	char *data = malloc(sizeof(char)*4095);
	char *buffer = data;
	FILE *f = fopen(file,"r");
	for(i=1;fread(buffer,1,1,f);++i) {
		data = realloc(data,i);
		buffer = data + (i - 1);
	}
	data = realloc(data,i + 1);
	memset(data + i,'\0',1);
	fclose(f);
	return data;
		
}

static int getStdOutInput(const char *command, char *buffer) {
	int ret = 0,i;
	char buf[1];
	FILE *fp = popen(command, "r");
	while((i=fread(buf,1,1,fp))) {
		memcpy(buffer + ret,buf,1);
		ret+=i;
	}
	fclose(fp);
	return ret;
}

int bat_parse(struct BatSt *st) {
	if((unsigned long)st & 3)
		printf("warning: 0x%x not aligned\n", (unsigned long)st);
	const char *command = "upower -i /org/freedesktop/UPower/devices/battery_BAT0 > btfile";
    char *buffer = read_file(command,"btfile");
	char buf[5000];
	char buf1[5000];
	st->pert = parse_str(buffer, buf);
	st->ret = parse_charge(buffer,buf1);
	free(buffer);
	return 1;
}
char *only_process_wrapper_str1() {
	char *__cmd = read_file("ps -a > pscmd","pscmd");
	size_t sz = strlen(__cmd);
	int nl_size =__calc_newline(__cmd,sz);
	int size_buffer = __calc_newline_buffer(__cmd);
	char *cmd = malloc(sizeof(char*)*size_buffer);
	memset(cmd + size_buffer - 1,'\0',2);
	memcpy(cmd,__cmd,size_buffer);
	free(__cmd);
	char **lines = split_ps_buffer(cmd,nl_size);
	char **procs = malloc(sizeof(char*)*nl_size);
	get_processes_pass(lines,procs,nl_size);	
	split_buffer_free(lines,nl_size +  1);

	int str_size = strlen(procs[nl_size - 2]);
	char *str = malloc((sizeof(char) * str_size) + 1);
	memcpy(str,procs[nl_size - 2], str_size);
	str[str_size] = '\0';
	//memset(str,'\0',100);
	//memcpy(str,procs[nl_size - 2],strlen(procs[nl_size - 2]));
	proc_free(procs,nl_size);//- 3);
	//proc_free(procs + nl_size - 1,1);
	free(cmd);
	free(procs);
	return str;
}


char *only_process_wrapper_str2() {
	char *cmd = read_file("ps -a > pscmd","pscmd");
	size_t sz = strlen(cmd);
	int nl_size =__calc_newline(cmd,sz);
	char **lines = split_ps_buffer(cmd,nl_size);
	char **procs = malloc(sizeof(char*)*nl_size);
	get_processes_pass(lines,procs,nl_size);	
	//char *str = store_process_string(procs,nl_size - 1,7);
	//printf("%d\n",nl_size);
	split_buffer_free(lines,nl_size);
	char *str = malloc(sizeof(char)*strlen(procs[nl_size - 2]));
	memset(str,'\0',strlen(procs[nl_size - 2]));
	memcpy(str,procs[nl_size - 2],strlen(procs[nl_size - 2]));
	proc_free(procs,nl_size - 1);
	free(cmd);
	free(procs);
	return str;
}

int only_process_wrapper(int offset) {
	char *cmd = stdout_getcmd("ps -a");
	int nl_size = calc_newline(cmd);
	char **procs = malloc(sizeof(char*)*nl_size + 1);
	char **lines = split_ps_buffer(cmd,nl_size);
	get_processes_non_alloc(lines,procs,nl_size);	
	print_process(procs,nl_size,offset);
	split_buffer_free(lines,nl_size);
	free(cmd);
	proc_free(procs,nl_size);
	free(procs);
	return 1;
 }

char *only_process_wrapper_str(int offset) {
	char *cmd = stdout_getcmd("ps -a");
	int nl_size = calc_newline(cmd);
	char **lines = split_ps_buffer(cmd,nl_size);
	char **procs = malloc(sizeof(char*)*nl_size);
	get_processes_pass(lines,procs,nl_size - 1);	
	char *str = store_process_string(procs,nl_size - 1,2);
	split_buffer_free(lines,nl_size);
	proc_free(procs,nl_size - 1);
	free(cmd);
	free(procs);
	return str;
}
char *process_wrapper_st() {
	char *cmd = read_file("ps -a > pscmd","pscmd");
	int nl_size = calc_newline(cmd);
	char **lines = split_ps_buffer(cmd,nl_size);
	char **procs = malloc(sizeof(char*)*nl_size);
	get_processes_pass(lines,procs,nl_size - 2);	
	char *proc = procs[nl_size - 3];
	split_buffer_free(lines,nl_size);
	proc_free(procs,nl_size - 2);
	free(cmd);
	free(procs);
	return proc;
}

