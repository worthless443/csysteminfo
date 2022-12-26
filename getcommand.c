#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include<batparse.h>

int getStdOutInput(const char *command, char *buffer) {
	char buf[1];
	FILE *fp = popen(command, "r");
	while(fread(buf,1,1,fp)) strcat(buffer,buf);
	fclose(fp);
}

int main() {
	char *buffer = malloc(sizeof(char)*2000);
	char buf[1000];
	char buf1[500];
	const char *command = "upower -i /org/freedesktop/UPower/devices/battery_BAT0";
	getStdOutInput(command, buffer);
	int pert = parse_str(buffer, buf);
	int ret = parse_charge(buffer,buf1);
	printf("battery is %s%d\%\n", ret ? "+" : "-", pert );
	//printf(buf1);
	free(buffer);
}
