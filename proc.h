void split_buffer_free(char **split_arr,int nl_size) ;
void proc_free(char **split_arr,int nl_size) ;
void make_it_parsable(char **split_arr, int nl_size) ;
char **get_processes(char **split_arr, int nl_size) ;
char **split_ps_buffer(char *buffer) ;
int calc_line_size(char *buffer,int line) ;
int calc_newline(char *buffer) ;
char *stdout_getcmd(const char *cmd) ;
void print_process(char **procs,int nl_size,int) ;
char *store_process_string(char **procs,int nl_size,int offset);
