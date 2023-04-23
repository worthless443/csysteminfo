#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include<batparse.h>
#include<proc.h>

static int getStdOutInput(const char *command, char *buffer) {
	int ret = 0,i;
	char buf[1];
	FILE *fp = popen(command, "rw");
	while((i=fread(buf,1,1,fp))) {
		strcat(buffer,buf);
		printf("%s\n",buffer);
		ret+=i;
	}
	fclose(fp);
	return ret;
}
int bat_parse(struct BatSt *st) {
	char buf[1000];
	char buf1[1000];
	const char *command = "upower -i /org/freedesktop/UPower/devices/battery_BAT0";
    char *buffer = stdout_getcmd(command);
	st->pert = parse_str(buffer, buf);
	st->ret = parse_charge(buffer,buf1);
	free(buffer);
	return 1;
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
	char *cmd = stdout_getcmd_constant("ps -a",10000);
	int nl_size = calc_newline(cmd);
	char **lines = split_ps_buffer(cmd);
	char **procs = get_processes(lines,nl_size);	
	char *proc_str = store_process_string(procs,nl_size,offset);
	split_buffer_free(lines,nl_size );
	proc_free(procs,nl_size);
	free(cmd);
	return proc_str;
}
