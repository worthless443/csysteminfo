int parse_str(const char *str, char *buf);
int parse_charge(const char *str, char *buf);
#ifdef __DEBUG_SYMBOLS
int getNLwholeChar(const char *str, const char *mat);
#endif
struct BatSt {
	int ret,pert;
};
int bat_parse(struct BatSt *);
int only_process_wrapper(int);
char *only_process_wrapper_str(int offset);
