#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#define MAXLENGTH 50000 
const char* program_name;

int getint(char *s){
	int i = 0;
	int p = 1;
	int len2 = strlen(s);
	int num = 0;
	for (i = 0; i<len2; i++){
		p = 1;
		int j = 0;
		for (j = 0; j<len2 - i - 1; j++){
			p = p * 10;
		}
		if (!(s[i] - '0' >= 0 && s[i] - '0' <= 9)){
			return -1;
		}
		else{
			num = num + p*(s[i] - '0');
		}
	}
	return num;
}

 void main(int argc,char *argv[]){
 	int i=0;
	int s=10; //number of street
	int n=5;  //number of line segment in each street
	int l=5;  //wait seconds
	int c=20; //range of coordinate
	int temp;
	for(i=1;i<argc;i++){
		if(argv[i][0]=='-'){
			temp=getint(argv[i+1]);
			if(temp!=-1){
				switch(argv[i][1]){
				case 's':
					s=temp;
					break;
				case 'n':
					n=temp;
					break;
				case 'l':
					l=temp;
					break;
				case 'c':
					c=temp;
					break;
			}
			}	
		i++;
		}
	}
	unsigned short r[4];
    FILE *f;
    f = fopen("/dev/random", "r");
    int j=0;
    char **str;
    str=malloc(1 * sizeof(int*));
    while(1){
       fread(r, 2, 4, f);
       printf("%f\n", (float)r[0]/65535);
       int ss=2+(int)((float)r[0]/65535.0*(float)(s-2+1));
	   if(ss=s+1) ss--;
	   cor = realloc(cor, (ss)*sizeof(int*));
	   for(j=0;j<ss;j++){
	   		

	   }

       sleep(5);
   }
   fclose(f);
 }