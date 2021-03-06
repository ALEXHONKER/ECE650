#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#define MAXLENGTH 50000 
const char* program_name;

struct street{
	int name;
	int len;//number of nodes
	int **cor;
	struct street * next;
};
int  interc(double x1,double y1,double x2,double y2,double x3,double y3, double x4,double y4){
	int interflag=0;
	double k2,b2,k1,b1;
	double xx,yy;
	double maxy,miny,maxy2,miny2,maxx,maxx2,minx,minxx,minxx2;
	if((x2-x1)==0.0){
		if((x4-x3)!=0.0){
			k2=(y4-y3)/(x4-x3);
			b2=y4-k2*x4;
			maxy=y1;
			miny=y2;
			if(y2>y1){
				maxy=y2;
				miny=y1;
			}	
			maxy2=y3;
			miny2=y4;
			if(y4>y3){
				maxy2=y4;
				miny2=y3;
			}	
			maxx=x3;
			minxx=x4;
			if(x4>x3){
				maxx=x4;
				minxx=x3;
			}	
			xx=x1;
			yy=k2*xx+b2;
			if (yy>=miny && yy<=maxy && yy>=miny2 && yy<=maxy2 && xx<=maxx && xx >= minxx){
				interflag=1;
			}
				
		}
			
		else if(x1==x3){
			maxy=y2;
			miny=y1;
			if(y1>y2){
				maxy=y1;
				miny=y2;
			}
			maxy2=y3;
			miny2=y4;
			if(y4>y3){
				maxy2=y4;
				miny2=y3;	
			}	
			if(maxy==miny2 || miny==maxy2){
				interflag=1;
			}
				
		}
			
	}else{
		k1=(y2-y1)/(x2-x1);
		b1=y2-k1*x2;
		if((x4-x3)==0){
			maxy=y1;
			miny=y2;
			if(y2>y1){
				maxy=y2;
				miny=y1;
			}
			maxy2=y3;
			miny2=y4;
			if(y4>y3){
				maxy2=y4;
				miny2=y3;
			}
			maxx=x1;
			minxx=x2;
			if(x2>x1){
				minxx=x1;
				maxx=x2;
			}	
			xx=x4;
			yy=k1*xx+b1;
			if (yy>=miny && yy<=maxy && yy<=maxy2 && yy>=miny2 && xx<=maxx && xx>=minxx){
				interflag=1;
			}
				
		}else{
			k2=(y4-y3)/(x4-x3);
			b2=y4-k2*x4;
			if(k1!=k2){
				maxx=x1;
				minxx=x2;
				if(x2>x1){
					maxx=x2;
					minxx=x1;
				}		
				maxx2=x3;
				minxx2=x4;
				if(x4>x3){
					maxx2=x4;
					minxx2=x3;
				}		
				maxy=y1;
				miny=y2;
				if(y2>y1){
					maxy=y2;
					miny=y1;
				}	
				maxy2=y3;
				miny2=y4;
				if(y4>y3){
					maxy2=y4;
					miny2=y3;
				}	
				xx=(b2-b1)/(k1-k2);
				yy=k1*xx+b1;
				if(xx>=minxx && xx<=maxx && yy>=miny && yy<=maxy && yy<=maxy2 && yy>=miny2 && xx<=maxx2 && xx >= minxx2){
					interflag=1;
				}
					
			}else{
				if((x1==x3 && y1==y3 ) || (x2==x3 && y2==y3) || (x1==x4 && y1==y4) || (x2==x4 && y2==y4)) 
					interflag=1;
			}
				
		}
			
	}	
	return interflag;
}

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

void forfree(struct street *f){
	while(f!=NULL){
		int i;
		for(i=f->len-1;i>=0;i--){
			free(f->cor[i]);
		}
		struct street *k=f;
		f=f->next;
		free(k);
	}
	return ;
}

int overlap(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
	int maxy;
	int miny;
	int maxy2;
	int miny2;
	if(x1==x2 && x4==x3 && x3==x1){
		maxy=y2;
		miny=y1;
		if(y1>y2){
			maxy=y1;
			miny=y2;
		}
		maxy2=y3;
		miny2=y4;
		if(y4>y3){
			maxy2=y4;
			miny2=y3;
		}
		
		if((miny2>=miny && miny2<maxy)||(maxy2<=maxy && maxy2>miny)){
			return 1;
		} 
		return 0;
	}else if((x1==x2 && x3!=x4)|| (x1!=x2 && x3==x4) ||(x1==x2 && x3==x4 && x1!=x3)){
		return 0;
	}else{
		float k2=((float)(y4-y3))/((float)(x4-x3));
		float b2=(float)y4-(k2*(float)x4);
		float k1=((float)(y2-y1))/((float)(x2-x1));
		float b1=(float)y2-(k1*(float)x2);
		if(k1==k2 && b1==b2){
			maxy=y2;
			miny=y1;
			if (y1>y2){
				maxy=y1;
				miny=y2;
			}	
			maxy2=y3;
			miny2=y4;
			if (y4>y3){
				maxy2=y4;
				miny2=y3;
			}
			int maxx=x2;
			int minx=x1;
			if(x1>x2){
				maxx=x1;
				minx=x2;
			}
			int maxx2=x3;
			int minx2=x4;
			if(x4>x3){
				maxx2=x4;
				minx2=x3;
			}
			if(k1!=0){
				if ((miny2>=miny && miny2<maxy)|| (maxy2<=maxy && maxy2>miny)){
					return 1;
				}		
			}	
			else{
				if((minx2>=minx && minx2<maxx) || (maxx2<=maxx && maxx2>minx)){
					return 1;
				}	
			}
		}
		return 0;
	}
}

int check(int x1,int y1,int x2, int y2, struct street *f){
	while(f!=NULL){
		//printf("name:%d\n",f->name);
		//printf("flen:%d\n",f->len);
		if(f->len>1){
			int i=0;
			int flag=0;
			for(i=1;i<f->len;i++){
				flag=overlap(x1,y1,x2,y2,f->cor[i-1][0],f->cor[i-1][1],f->cor[i][0],f->cor[i][1]);
				if(flag==1) return 1;
			}
		}
		f=f->next;
	}
	return 0;
}
int checkintsec(int x1,int y1,int x2, int y2, struct street *f){
	if(f!=NULL){
		//printf("name:%d\n",f->name);
		//printf("flen:%d\n",f->len);
		if(f->len>2){
			int i=0;
			int flag=0;
			for(i=1;i<f->len-1;i++){
				flag=interc(x1,y1,x2,y2,f->cor[i-1][0],f->cor[i-1][1],f->cor[i][0],f->cor[i][1]);
				if(flag==1) return 1;
			}
		}
	}
	return 0;
}
 void main(int argc,char *argv[]){
 	int i=0;
	int s=10; //number of street
	//int n=5;  //number of line segment in each street
	int n=5;
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
	//unsigned short r[4];
	unsigned short seed;
	unsigned short ran[50000];
    FILE *f;
    f = fopen("/dev/urandom", "r");
    int j=0;
    char **str;
    str=malloc(1 * sizeof(int*));
    int count=0;
    fread(&ran, 2, 49000, f);
    struct street *s1;
    while(1){
    	if(count>48000) {
    		fclose(f);
    		f = fopen("/dev/urandom", "r");
    		fread(&ran, 2, 49000, f);
    		count=0;
    	}
      // printf("%f\n", (float)seed/65535);
       int ss=2+(int)((float)ran[count++]/65535.0*(float)(s-1));
	   if(ss==s+1) ss--;
	  // cor = realloc(cor, (ss)*sizeof(int*));
	   int numstr=0;
	   struct street *first=NULL;
	//   printf("ss:%d\n",ss);
	   for(j=0;j<ss;j++){
	   		 s1=malloc(sizeof(struct street));
	   		 s1->next=first;
	   		 s1->name=j;
	   		 first=s1;
	   		 //fread(&seed, 2, 1, f);
	   		 int nn=2+(int)((float)ran[count++]/65535.0*(float)(n));
	   		 if(nn==n+1) nn--;
	   		// printf("nn:%d\n",nn);
	   		 s1->cor=malloc((nn+1)*sizeof(int*));
	   		 s1->len=nn+1;
	   		 for(i=0;i<=nn;i++){
	   		 	//printf("i:%d\n",i);
	   		 	s1->cor[i]=malloc(2*sizeof(int));
	   		 	//unsigned short co[2];
	   		 	//fread(co,2,1,f);
	   		 	int cc1,cc2;
	   		 	if(i>=1){
	   		 		int k=0;
	   		 		if(i>=3){
	   		 			for(k=0;k<26;k++){
		   		 			cc1=-1*c+(int)((float)ran[count++]/65535.0*(float)(2*c+1));
		   		 			if(cc1==c+1) cc1--;
		   		 			cc2=-1*c+(int)((float)ran[count++]/65535.0*(float)(2*c+1));
		   		 			if(cc2==c+1) cc2--;
		   		 			// printf("ss+");
		   		 			// int fu=0;
		   		 			// fu= checkintsec((double)cc1,(double)cc2,(double)s1->cor[i-1][0],(double)s1->cor[i-1][1],first);
		   		 			// printf("ss1+\n");
		   		 			// if(fu==1) {k--;continue;}
		   		 			// if(check(cc1,cc2,s1->cor[i-1][0],s1->cor[i-1][1],first)==0 && fu==0 &&!(cc1==s1->cor[i-1][0] && cc2==s1->cor[i-1][1])) break;
		   		 			// printf("ss2\n");
		   		 			if(check(cc1,cc2,s1->cor[i-1][0],s1->cor[i-1][1],first)==0  &&!(cc1==s1->cor[i-1][0] && cc2==s1->cor[i-1][1])) break;
	   		 			}
	   		 		}else{
	   		 			for(k=0;k<26;k++){
		   		 			cc1=-1*c+(int)((float)ran[count++]/65535.0*(float)(2*c+1));
		   		 			if(cc1==c+1) cc1--;
		   		 			cc2=-1*c+(int)((float)ran[count++]/65535.0*(float)(2*c+1));
		   		 			if(cc2==c+1) cc2--;
		   		 			if(check(cc1,cc2,s1->cor[i-1][0],s1->cor[i-1][1],first)==0 && !(cc1==s1->cor[i-1][0] && cc2==s1->cor[i-1][1])) break;
	   		 			}
	   		 		}
	   		 		if(k==26){
	   		 			fprintf(stderr,"Error:  failed to generate valid input for 25 simultaneous attempts\n");
	   		 			fflush(stderr);
	   		 			return ;
	   		 			/////////////////////////////////////////////////////////////////////////////////////////
	   		 			/*
							end all the processes~~~~~~~to be completed 
	   		 			*/
	   		 			//////
	   		 		}
	   		 	}else{
	   		 		cc1=-1*c+(int)((float)ran[count++]/65535.0*(float)(2*c+1));
	   		 		if(cc1==c+1) cc1--;
	   		 		cc2=-1*c+(int)((float)ran[count++]/65535.0*(float)(2*c+1));
	   		 		if(cc2==c+1) cc2--;
	   		 	} 
	   		 	//printf("i:%d\n",i);
	   		 	//printf("cc1:%d\n",cc1);
	   		 	//printf("cc2:%d\n",cc2);
	   		 	s1->cor[i][0]=cc1;
	   		 	s1->cor[i][1]=cc2;
	   		 	s1->len=i+1;
	   		 }
	   }
	   struct street *st=first;
	 //  char command=malloc(sizeof(char)*10000);
	  // strcpy(command,"r\n");


	   fprintf(stdout,"r\n");
	  // fprintf(stdout,"r\n");
	   while(st!=NULL){   	 
	   	 fprintf(stdout,"a \"%d\" ",st->name);
	   	 int te=0;
	   	 for(te=0;te<st->len;te++){
	   	 	fprintf(stdout,"(%d,%d) ",st->cor[te][0],st->cor[te][1]);
	   	 }
	   	 fprintf(stdout,"\n");
	   	 st=st->next;
	   }
	   fprintf(stdout,"g\n");
	   fflush(stdout);
	   int ll=5+(int)((float)ran[count++]/65535.0*(float)(l-4));
	   forfree(first);
       sleep(1);////////////////////////////////
   }
   fclose(f);
 }