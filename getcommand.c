#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include<batparse.h>

extern int memused_wrapper();  // nigger

int getStdOutInput(const char *command, char *buffer) {
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
int main() {
	char *buffer = malloc(sizeof(char)*2000);
	char buf[1000];
	char buf1[500];
	const char *command = "upower -i /org/freedesktop/UPower/devices/battery_BAT0";
	getStdOutInput(command, buffer);
	int pert = parse_str(buffer, buf);
	int ret = parse_charge(buffer,buf1);
	printf("battery: %s%d\%\n", ret ? "+" : "-", pert);
	printf("ramused: %dMiB\n", memused_wrapper());
	free(buffer);
}
