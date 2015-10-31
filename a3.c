#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXLENGTH 50000 
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

 void main(){
 	char *name;
 	unsigned maxl=MAXLENGTH;
 	name=malloc(sizeof(char)*MAXLENGTH)
 	name = (char *)malloc(maxl * sizeof(char));
 	while (getline(&name,&maxl,stdin)!=EOF){
 		//S N L C
		name[strlen(name)-1]='\0';
		int i=0;
		int s=10;
		int n=5;
		int l=5;
		int c=20;
		char num=(char *)malloc(100 * sizeof(char));
		int p=0;
		int indic=0;
		int fault=0;
		char connmand;
		for(i=1;i<strlen(name);i++){
			if(name[i-1]=='-'){
				indic=1;
				int j=0;
				command=name[i];
				for(i=i+2;j<strleng(name);i++){
					if(name[i]!=' '){
						num[p++]=name[i];
					}else{
						break;
					}
				}
				int argu=getint(num);
				if(arug==-1){
					fprintf(stderr, "Error: Wrong input of the parameter.\n");
					fault=1;
					break;
				}
				if(command=='s') s=argu;
				else if(commmand=='n') n=argu;
				else if(command=='l') n=argu;
				else if(command=='c') c=argu;
			memset(num, 0, 100* sizeof(char));
			}

		}
		if(fault==1) {
			memset(name, 0, maxl * sizeof(char));
			continue;
		}
		

 }