#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int tempread(char *device, int verbose);
void usage();

#define  BUFFERSIZE  128
char *device = "28-02131338abaa";
int verbose = 0;

int main(int argc, char *argv[])
{
    /* process the arguments */
    argc--; argv++;  
    while(argc > 0) {
	if(!strcmp("-v", argv[0])) {     /* if -v*/
		verbose = 1;
 	}
    	else if(!strcmp("-d", argv[0])) {  /* if -d*/
    		argc--; argv++;
    		if(argc == 0){  /*if no ID*/ 
    			usage();
    			exit(1);
    		}

		device = argv[0];
	    	argc--; argv++;
    		}

	else
	usage();
	argc--; argv++;
	}
    tempread(device, verbose);
    exit(0);
}

int tempread(char *device, int verbose){

    char addr[60];
    int temp;
    int i, j, fd, ret;

    char buf[BUFFERSIZE];
    char tempBuf[5];
    char tempnum[20];

    sprintf(addr, "/sys/bus/w1/devices/%s/w1_slave",device);
    fd = open(addr, O_RDONLY);
    if(fd == -1){
	printf("%d\n",1);
	return 1;
	}

    while(1){
	ret = read(fd, buf, BUFFERSIZE);
    if(verbose == 1 && ret>0){
        char *fin = malloc(100);
        sprintf(fin, "cat /sys/bus/w1/devices/%s/w1_slave", device);
        system(fin);

    }
	if(ret == 0){
		break;
	}
	if(ret == -1){
	printf("%d\n",1);
	close(fd);
	return 1;
	}
    }

	for(i=0;i<sizeof(buf);i++){
		if(buf[i] == 't'){
			for(j=0;j<sizeof(tempBuf);j++){
				tempBuf[j] = buf[i+2+j];
			}
		}
	}

    temp = atoi(tempBuf);
    printf("%d\n",temp);
    close(fd);
    return temp;
}

void usage(){
     printf("USAGE\n\n");
     printf("run without arguments to display the default device's temperature\n");
     printf("enter -v to display the file content\n");
     printf("enter -d device to define your device number\n");
}
