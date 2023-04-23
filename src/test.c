#include<batparse.h>
#include<proc.h>
#include<stdio.h>
#include<stdlib.h>
int main() {
	while(1) {
		char *cmd = stdout_getcmd("ps -a");
		int nl_size = calc_newline(cmd);
		char **lines = split_ps_buffer(cmd);
		char **procs = get_processes(lines,nl_size);	
		//char *buf = only_process_wrapper_str(5);
		char *str = store_process_string(procs,nl_size,2);
		printf("%s\n",str);
		free(str);
		//split_buffer_free(lines,nl_size - 1);
		//proc_free(procs,nl_size);
		//free(cmd);
		sleep(1);
	}
}
