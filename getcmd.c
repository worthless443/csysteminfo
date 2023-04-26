#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include<batparse.h>
#include<proc.h>

int __calc_newline(char *cmd) {
	int nl = 0;
	for(int i = 0;i<strlen(cmd) - 1;++i)  {
		if(cmd[i] == '\n') ++nl;
		if(cmd[i] == 'p' && cmd[i + 1]=='s') break;
	}
		
	return nl;
}

char *read_file(const char *cmd, const char *file) {
	int ret = system(cmd);
	char *data = malloc(sizeof(char)*4095);
	char *buffer = data;
	FILE *f = fopen(file,"r");
	for(int i=1;fread(buffer,1,1,f);++i) {
		data = realloc(data,sizeof(char)*i);
		buffer = data + (i - 1);

	}
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
	char *cmd = read_file("ps -a > pscmd","pscmd");
	int nl_size =__calc_newline(cmd);
	char **lines = split_ps_buffer(cmd);
	char **procs = malloc(sizeof(char*)*nl_size);
	get_processes_pass(lines,procs,nl_size - 1);	
	//char *str = store_process_string(procs,nl_size - 1,7);
	//printf("%d\n",nl_size);
	split_buffer_free(lines,nl_size);
	char *str = procs[nl_size - 2];
	proc_free(procs,nl_size - 1);
	free(cmd);
	free(procs);
	return str;
}


char *only_process_wrapper_str2() {
	char *cmd = read_file("ps -a > pscmd","pscmd");
	int nl_size =__calc_newline(cmd);
	char **lines = split_ps_buffer(cmd);
	char **procs = malloc(sizeof(char*)*nl_size);
	get_processes_pass(lines,procs,nl_size - 1);	
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
	char **lines = split_ps_buffer(cmd);
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
	char **lines = split_ps_buffer(cmd);
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
	char **lines = split_ps_buffer(cmd);
	char **procs = malloc(sizeof(char*)*nl_size);
	get_processes_pass(lines,procs,nl_size - 2);	
	char *proc = procs[nl_size - 3];
	split_buffer_free(lines,nl_size);
	proc_free(procs,nl_size - 2);
	free(cmd);
	free(procs);
	return proc;
}

