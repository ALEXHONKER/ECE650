// #include <stdio.h>
// // #include <string.h>
// // #include <stdlib.h>
// // #include <unistd.h> 
// // #include <fcntl.h>
// // #include <linux/random.h>
// // #include <math.h>
// void main(){}
// 	//int byte_count = 64;
// 	unsigned int data;
// 	//char data[64];
// 	FILE *fp;
// 	fp=fopen("/dev/urandom", "r");
// 	fread(&data,sizeof(data),1,fp);
// 	fclose(fp);
// 	printf("second:%s\n",data);
// }

#include <stdio.h>
    
    int
    main(int argc, char **argv)
    {
    	int s=10;
        unsigned  short r[4];
        FILE *f;
        f = fopen("/dev/random", "r");
//    while(1){
       fread(r, 2, 4, f);
        int ss=2+(int)((float)r[0]/65535.0*(float)(s-2+1));
       // printf("%f\n", (float)r[0]/65535);
       if(ss=s+1) ss--;
       int t=fork();
       if(t!=0){
       	 printf(stdout,"%d\n", ss);
       }else{
       	exec()
       }
       
 //  }
   fclose(f);
       return 0;
   }