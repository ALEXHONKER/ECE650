#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
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
 	char line[MAXLENGTH*100];
 	unsigned long maxl2=MAXLENGTH;
 	char pyout2[MAXLENGTH*1000];
 	char pyerr[MAXLENGTH];
 	strcpy(command,"./rgen ");
 	char a3out[1000];
 	//char *command=malloc(sizeof(char));
 	int flags=0,flagn=0,flagl=0,flagc=0;
 	for(i=1;i<argc;i++){
		if(argv[i][0]=='-'){
			temp=getint(argv[i+1]);
			if(temp!=-1){
				switch(argv[i][1]){
				case 's':
					if(flags==0){
						flags=1;
					}else{
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
					break;
				case 'l':
					if(flagl==0){
						flagl=1;
					}else{
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
					break;
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
 	fprintf(stdout,"%s\n",command);
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

 			fprintf(stdout, "child.\n" );
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
		fprintf(stdout, "parent1\n" );
		unsigned long len=100;
		char *command_path=malloc(sizeof(char)*100);

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

		while(getline(&name,&maxl,fp)!=EOF){
			//fprintf(stdout,"%s",name);
			strcat(line,name);
			if(name[0]=='g'){// always g????????????????????????????????????????????????????????????????
				write(fd1[1],line,strlen(line)+1);
				fprintf(stdout,"%s",line);
				strcpy(pyout2,"\0");
				read(fd2[0],pyout2,sizeof(char)*MAXLENGTH*1000);
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
				fprintf(stdout, "21111111111111111111111111111111\n");
				// if(fgets (command_path, 1000, stdin)==NULL){
				// 	fprintf(stdout, "madan" );
				// 	break;
				// }
				if(getline(&command_path,&len,stdin)==EOF){
					fprintf(stdout, "madan\n" );
					fflush(stdout);
					break;
				}
				command_path[strlen(command_path)-1]=='\0';
				fprintf(stdout,"%s",command_path);
				fprintf(stdout, "2333333333333333333333333333333333333\n");

				
				strcat(pyout2,command_path);
				fprintf(stdout, "pyout2:%s", pyout2);
				//fflush(stdout);
				

				
				write(fd11[1],pyout2,strlen(pyout2)+1);
 				read(fd22[0],a3out,1000);
 				int errflag2=0;
 				fprintf(stdout, "235555555555555555555555555555\n");
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
				//fprintf(stdout,"command:%s\n",command_path);

				memset(pyerr,0,sizeof(char)*MAXLENGTH);
				memset(command_path,0,sizeof(char)*100);
				memset(a3out,0,sizeof(char)*1000);
				memset(command,0,sizeof(char)&len);
				memset(pyout2,0,sizeof(char)*MAXLENGTH*1000);
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