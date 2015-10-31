#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h>
#include <math.h>
void main(){}
	int byte_count = 64;
	char data[64];
	FILE *fp;
	fp = fopen("/dev/urandom", "r");
	fread(&data, 1, byte_count, fp);
	fclose(fp);
	printf("second:%s\n",data);
	printf("second:%d\n",byte_count);
}