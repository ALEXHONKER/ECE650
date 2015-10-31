#include <stdio.h>
void main(){
	unsigned long max=1000;
	char *str=(char*)malloc(sizeof(char)*max);
	while(getline(&str,&max,stdin)!=EOF){
		printf("this is : %s",str);
	}
}