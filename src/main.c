#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include<batparse.h>

extern int memused_wrapper();  // nigger


static char *parse_arg(char *rawarg) {
	return rawarg + 2;	
}
static char *parse_opt(char *rawarg) {
	return rawarg + 1;
}

int main(int argc, char **argv) {
	int showmem = 0, showbat=0,showproc = 0,poff = 1;
	if(argc<2) showbat = 1;
	else {
		for(int i=1;i<argc;++i) {
			//printf("%s\n",argv[i]);
			if(0==strcmp(parse_arg(argv[i]),"all"))	{
				showmem = 1;
				showbat = 1;
				showproc = 1;
			}
			else if(0 == strcmp(argv[i],"-proc"))	
				showproc  = 1;
			else if(0==strcmp(argv[i],"-p"))	
				showproc  = 1;
			else if(0==strcmp(parse_arg(argv[i]),"bat"))	
				showbat  = 1;
			else if(0==strcmp(parse_arg(argv[i]),"mem"))	
				showmem = 1;
			else if(0==strcmp(parse_opt(argv[i]),"m"))	
				showmem = 1;
			else if(0==strcmp(parse_opt(argv[i]),"b"))	
				showbat = 1;
			else if(0==strcmp(parse_opt(argv[i]),"a")) {
				showbat = 1;
				showmem = 1;
				showproc = 1;
			}
			else if(0 == strcmp(argv[i],"--poff"))	
				poff  = atoi(argv[++i]);
			else {
				fprintf(stderr, "\'%s\': not recognized\n", !(*parse_arg(argv[i]) >= 'a' && *parse_arg(argv[i] )<= 'z') ? parse_opt(argv[i]) : parse_arg(argv[i]));
				return 1;
			}
		}
	}
	char *str = only_process_wrapper_str(poff);
	struct BatSt st;
	bat_parse(&st);
	int ramused = memused_wrapper();
	if(showproc)
		printf("%s\n",str);
	if(showbat)
		printf("battery: %s%d\%\n", st.ret ? "+" : "-", st.pert);
	if(showmem)
		printf("ramused: %dMiB\n", ramused);
	free(str);
}
