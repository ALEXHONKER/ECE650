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
 	//char *command=malloc(sizeof(char));
 	for(i=1;i<argc;i++){
 		strcat(command,argv[i]);
 		strcat(command," ");
 	}
 	//fprintf(stdout,"%s\n",command);
 	FILE *fp;
 	FILE *a2;// get a2's out put
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
 		pid_t prgen;//process of rgen
 		prgen=fork();
 		if(prgen==0){

 			//fprintf(stdout, "child.\n" );
 			close(fd1[1]);
 			close(fd2[0]);
 			//close(fd3[0]);
 			dup2(fd2[1],STDOUT_FILENO);
			dup2(fd1[0],STDIN_FILENO);
			//dup2(fd3[1],STDERR_FILENO);
			//dup2(fd2[1],1);
			//dup2(fd1[0],0);
			//close(fd3[1]);
			close(fd2[1]);
			close(fd1[0]);
			//char* cc[]={"a1-ece650.py",NULL};
			//sleep(1);
			//execl("/bin/sh","sh","-c","python ./a1-ece650.py",NULL);
			execl("/bin/sh","sh","-c","python ./a1-ece650.py",NULL);
			fprintf(stderr, "Error: Open python script failed.\n" );
 			return 0;
 		}
		close(fd1[0]);
		close(fd2[1]);
		strcpy(line,"\0");
		//fprintf(stdout, "parent1\n" );
		unsigned long len=100;
		char *command_path=malloc(sizeof(char)*100);

		

		while(getline(&name,&maxl,fp)!=EOF){
			//fprintf(stdout,"%s",name);
			strcat(line,name);
			if(name[0]=='g'){// always g????????????????????????????????????????????????????????????????
				write(fd1[1],line,strlen(line)+1);
				fprintf(stdout,"%s",line);
				strcpy(pyout2,"\0");
				//read(fd2[0],pyout2,sizeof(char)*MAXLENGTH*1000);
				read(fd2[0],temp,sizeof(char)*4095);
				strcat(pyout2,temp);
				while(temp[strlen(temp)-2]!='}'){
					//fprintf(stdout,"oheeeeeeeeeeee\n");
					memset(temp,0,sizeof(char)*4095);
					read(fd2[0],temp,sizeof(char)*4095);
					//fprintf(stdout,"lenoftemp:%d,%c\n",(int)strlen(temp),temp[strlen(temp)-2]);
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
					//fprintf(stdout,"length:%d\n",(int)strlen(pyout2));
					fprintf(stdout,"%s",pyout2);
				}
				if(getline(&command_path,&len,stdin)==EOF){
					fprintf(stdout, "madan\n" );//////////////////////////
					//fflush(stdout);
					
					// write(fd1[1],NULL,1);
					close(fd1[1]);
					// close(fd2[0]);
					// close(fd1[0]);
					// close(fd2[1]);
					fprintf(stdout, "madan3\n" );
					//pclose(fp);
					// if (pclose (fp) != 0)
				 //    {
				 //      fprintf (stderr,"Could not run more or other error.\n");
				 //    }
					
					//kill(prgen, SIGKILL);
					fprintf(stdout, "madan4\n" );
					//goto ks;
					exit(1);
					exit(0);
					return 0;
					//break;
				}
				command_path[strlen(command_path)-1]=='\0';
				strcat(pyout2,command_path);
				int fd11[2],fd22[2];
 				if(pipe(fd11)<0 || pipe(fd22)<0){
 					fprintf(stderr, "Error: Creat pipes failed.\n" );
 					///////////////kill
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
 				//fprintf(stdout, "235555555555555555555555555555\n");
 				fflush(stdout);
 				////if error need exit??????????????????????????????????????????????
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
				// else{
				// 	kill(prgen, SIGKILL);
				// 	kill(p2, SIGKILL);
				// 	pclose(fp);
 			// 		return 0;
				// 	break;
				// }
				//fprintf(stdout,"command:%s\n",command_path);
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
 		

 	}
 	pclose(fp);
 	return 0;
 }