#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include<batparse.h>

static int getStdOutInput(const char *command, char *buffer) {
	int ret = 0,i;
	char buf[1];
	FILE *fp = popen(command, "r");
	while((i=fread(buf,1,1,fp))) {
		strcat(buffer,buf);
		ret+=i;
	}
	fclose(fp);
	return ret;
}
int bat_parse(struct BatSt *st) {
    char *buffer = malloc(sizeof(char)*2000);
	char buf[1000];
	char buf1[1000];
	const char *command = "upower -i /org/freedesktop/UPower/devices/battery_BAT0";
	getStdOutInput(command, buffer);
	st->pert = parse_str(buffer, buf);
	st->ret = parse_charge(buffer,buf1);
	free(buffer);
	return 1;
}
