#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXLENGTH 500
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

 int main(int argc,char *argv[]){
 	int i=0;
 	unsigned long maxl=MAXLENGTH;
 	char *name=malloc(maxl*sizeof(char));
 	char command[10000];
 	char line[MAXLENGTH*100];
 	unsigned long maxl2=MAXLENGTH;
 	char *pyout=malloc(maxl2*sizeof(char));
 	char pyout2[MAXLENGTH*100];
 	strcpy(command,"./rgen ");
 	//char *command=malloc(sizeof(char));
 	for(i=1;i<argc;i++){
 		strcat(command,argv[i]);
 		strcat(command," ");
 	}
 	fprintf(stdout,"%s\n",command);
 	FILE *fp;
 	if((fp=popen(command,"r"))==NULL){
 		fprintf(stderr, "Error: Fail to open rgen.\n" );
 		return 0;
 	}else{
 		// while(getline(&name,&maxl,fp)!=EOF){
 		// 	fprintf(stdout,"%s",name);
 		// 	memset(name, 0, maxl * sizeof(char));
 		// }
 		int fd1[2],fd2[2];
 		if(pipe(fd1)<0 || pipe(fd2)<0){
 			fprintf(stderr, "Error: Creat pipes failed.\n" );
 			return 0;
 		}
 		if(fork()==0){

 			fprintf(stdout, "child.\n" );
 			close(fd1[1]);
 			close(fd2[0]);
 			dup2(fd2[1],STDOUT_FILENO);
			dup2(fd1[0],STDIN_FILENO);
			//dup2(fd2[1],1);
			//dup2(fd1[0],0);
			close(fd2[1]);
			close(fd1[0]);
			char* cc[]={"a1-ece650.py",NULL};
			//sleep(1);
			//execl("/bin/sh","sh","-c","python ./a1-ece650.py",NULL);
			execl("/bin/sh","sh","-c","python ./a1-ece650.py",NULL);
			fprintf(stderr, "Error: Open python script failed.\n" );
 			return 0;
 		}
		close(fd1[0]);
		close(fd2[1]);
		strcpy(line,"\0");
		fprintf(stdout, "parent1\n" );
		while(getline(&name,&maxl,fp)!=EOF){
			//fprintf(stdout,"%s",name);
			strcat(line,name);
			if(name[0]=='g'){
				write(fd1[1],line,strlen(line)+1);
				//fprintf(py,"%s",line);
				//fprintf(stdout,"%s",line);
				//fprintf(stdout,"=======================================================");
				 //sleep(3);
				 //fprintf(stdout, "after sleep\n" );
				strcpy(pyout2,"\0");
				read(fd2[0],pyout2,sizeof(char)*MAXLENGTH*100);
				//close(fd2[0]);
				//close(fd1[1]);
				// while(getline(&pyout,&maxl2,py)!=EOF){
				// 	strcat(pyout2,pyout);
				// }
				fprintf(stdout,"%s",pyout2);
				memset(pyout2,0,sizeof(char)*MAXLENGTH*100);
				memset(line,0,sizeof(char)*MAXLENGTH*100);
			}
			memset(name, 0, maxl * sizeof(char));
		}	
 		// if((py=popen("python a1-ece650.py","w"))==NULL){
 		// 	fprintf(stderr, "Error: Fail to open rgen.\n" );
 		// }else{
 		// 	fprintf(stdout,"232323232");
 		// 	strcpy(line,"\0");
 		// 	while(getline(&name,&maxl,fp)!=EOF){
	 	// 		//fprintf(stdout,"%s",name);
 		// 		strcat(line,name);
 		// 		if(name[0]=='g'){
 		// 			fprintf(py,"%s",line);
 		// 			//fprintf(stdout,"%s",line);
 		// 			strcpy(pyout2,"\0");
 		// 			while(getline(&pyout,&maxl2,py)!=EOF){
 		// 				strcat(pyout2,pyout);
 		// 			}
 		// 			fprintf(stdout,"%s",pyout2);
 		// 			memset(line,0,sizeof(char)*MAXLENGTH*100);
 		// 		}
	 	// 		memset(name, 0, maxl * sizeof(char));
 		// 	}	
 		// }
 		//pclose(py);

 	}
 	pclose(fp);
 return 0;
 }