#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/user.h>
#define MAXLENGTH 5000
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
 	char line[MAXLENGTH*10];
 	unsigned long maxl2=MAXLENGTH;
 	char pyout2[MAXLENGTH*1000];
 	char pyerr[MAXLENGTH];
 	strcpy(command,"./rgen ");
 	char a3out[1000];
 	char temp[4095];
 	//check the valid of command=line arguments
 	int flags=0,flagn=0,flagl=0,flagc=0;
 	for(i=1;i<argc;i++){
		if(argv[i][0]=='-'){
			int tp=getint(argv[i+1]);
			if(tp!=-1){
				switch(argv[i][1]){
				case 's':
					if(flags==0){
						flags=1;
					}else{
						fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 						return 0;
					}
					if(tp<2){
						fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 						return 0;
					}
					break;
				case 'n':
					if(flagn==0){
						flagn=1;
					}else{
						fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 						return 0;
					}
					if(tp<1){
						fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 						return 0;
					}
					break;
				case 'l':
					if(flagl==0){
						flagl=1;
					}else{
						fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 						return 0;
					}
					if(tp<5){
						fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 						return 0;
					}
					break;
				case 'c':
					if(flagc==0){
						flagc=1;
					}else{
						fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 						return 0;
					}
					if(tp<1){
						fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 						return 0;
					}
					break;
				default:
					fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 					return 0;
				}
			}else{
				fprintf(stderr, "Error: Invalid command-line arguments.\n" );
 				return 0;
			}	
		i++;
		}
	}

 	for(i=1;i<argc;i++){
 		strcat(command,argv[i]);
 		strcat(command," ");
 	}
 	FILE *a2;// get a2's out put
 	int fd0[2];
 	if(pipe(fd0)<0){
			fprintf(stderr, "Error: Creat pipes failed.\n" );
 			return 0;
 	}
 	pid_t prgen;
 	prgen=fork();
 	if(prgen==0){
 		close(fd0[0]);
 		dup2(fd0[1],STDOUT_FILENO);
 		close(fd0[1]);
 		execl("/bin/sh","sh","-c",command,NULL);
		fprintf(stderr, "Error: Fail to open rgen.\n" );
 		return 0;
 	}
 	//close(fd0[1]);
 	char *c;
 	c=malloc(sizeof(char)*1);
 	c[0]='r';
 	FILE *fp = fdopen(fd0[0], c); //don't use fopen, which can not terminate the child process
    close(fd0[1]);
	int fd1[2],fd2[2];
	if(pipe(fd1)<0 || pipe(fd2)<0){
		fprintf(stderr, "Error: Creat pipes failed.\n" );
		return 0;
	}
	pid_t ppy;//process of rgen
	ppy=fork();
	if(ppy==0){
		close(fd1[1]);
		close(fd2[0]);
		dup2(fd2[1],STDOUT_FILENO);
		dup2(fd1[0],STDIN_FILENO);
		close(fd2[1]);
		close(fd1[0]);
		execl("/bin/sh","sh","-c","python ./a1-ece650.py",NULL);
		fprintf(stderr, "Error: Open python script failed.\n" );
			return 0;
	}
	close(fd1[0]);
	close(fd2[1]);
	strcpy(line,"\0");
	unsigned long len=100;
	char *command_path=malloc(sizeof(char)*100);
	while(getline(&name,&maxl,fp)!=EOF){
		if(strlen(name)>=5&&name[0]=='E'&&name[1]=='r'){
			fprintf(stderr, "%s",name);
			close(fd1[1]);
			close(fd0[0]);
			exit(1);
			exit(0);
			return 0;
		}
		strcat(line,name);
		if(name[0]=='g'){// always g????????????????????????????????????????????????????????????????
			///////////////////////////////if over 25 time ,generate Error:!!!!!!!!!sloved~~
			write(fd1[1],line,strlen(line)+1);
			fprintf(stdout,"%s",line);
			strcpy(pyout2,"\0");
			memset(temp,0,sizeof(char)*4095);
			read(fd2[0],temp,sizeof(char)*4095);////////////////////will it over 4096  check stderr
			strcat(pyout2,temp);
			while(temp[strlen(temp)-2]!='}'){
				memset(temp,0,sizeof(char)*4095);
				read(fd2[0],temp,sizeof(char)*4095);
				strcat(pyout2,temp);
			}
			memset(temp,0,sizeof(char)*4095);
			int ii=0;
			int errflag=0;
			for(ii=3;ii<strlen(pyout2);ii++){
				if(pyout2[ii-2]=='E'){
					if(pyout2[ii-1]=='r'&& pyout2[ii]=='r'){
						fprintf(stderr,"%s",pyout2);
						errflag=1;
						break;
					}else{
						break;
					}			
				}
			}
			if(errflag==0&&strlen(pyout2)!=0){
				fprintf(stdout,"%s",pyout2);
			}

			if(getline(&command_path,&len,stdin)==EOF){
				close(fd1[1]);
				close(fd0[0]);
				exit(1);
				exit(0);
				return 0;
			}

			command_path[strlen(command_path)-1]='\0';
			strcat(pyout2,command_path);
			int fd11[2],fd22[2];
				if(pipe(fd11)<0 || pipe(fd22)<0){
					fprintf(stderr, "Error: Creat pipes failed.\n" );
					///////////////kill
					close(fd1[1]);
					close(fd0[0]);
					exit(1);
					exit(0);
					return 0;
				}
			pid_t p2;//process of a2
			p2=fork();
			if(p2==0){
				close(fd11[1]);
				close(fd22[0]);
				dup2(fd22[1],STDOUT_FILENO);
				dup2(fd11[0],STDIN_FILENO);
				close(fd22[1]);
				close(fd11[0]);
				execl("/bin/sh","sh","-c","./a2-ece650",NULL);
				fprintf(stderr, "Error: Open python script failed.\n" );
				return 0;
			}
			close(fd11[0]);
			close(fd22[1]);
			write(fd11[1],pyout2,strlen(pyout2)+1);
			read(fd22[0],a3out,1000);
			int errflag2=0;
			fflush(stdout);
			for(ii=0;ii<strlen(a3out);ii++){
				if(a3out[ii]=='E'){
					fprintf(stderr, "%s", a3out);
					errflag2=1;
					break;
				}
			if(ii>3) break;
			}
			if(errflag2==0){
				fprintf(stdout, "%s",a3out);
			}
			close(fd11[1]);
			kill(p2, SIGKILL);
			memset(pyerr,0,sizeof(char)*MAXLENGTH);
			memset(command_path,0,sizeof(char)*100);
			memset(a3out,0,sizeof(char)*1000);
			memset(command,0,sizeof(char)&len);
			memset(pyout2,0,sizeof(char)*MAXLENGTH*1000);
			memset(line,0,sizeof(char)*MAXLENGTH*10);
		}
		memset(name, 0, maxl * sizeof(char));
	}		
 	close(fd1[1]);
	close(fd0[0]);
	exit(1);
	exit(0);
	return 0;
 	return 0;
 }