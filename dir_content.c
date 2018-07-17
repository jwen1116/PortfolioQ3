//Question 4

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 512

int main(int argc,char** argv)
{
	int file,destination,r_file,w_file,n;
	char buf [BUFSIZE];

	if ((file=open(argv[1],O_RDONLY))<0){
		perror("Error opening source file !");
		exit(1);
	}

	if ((destination=creat(argv[2],0666))<0){
		perror("Error creating destination file!");
		exit(2);
	}

	while ((r_file=read(file,buf,sizeof(buf))) != 0){
		if (r_file<0){
			perror("Error reading source file!");
			exit(3);
		}
		w_file=0;
		do{
			if ((n=write(destination,&buf[w_file],r_file-w_file))<0){
				perror("Error writing destination file!");
				exit(4);
			}
			w_file+=n;
		}
		while (w_file<r_file);}
	close(file);close(destination);

	DIR *d;
	struct dirent *dir;
	d=opendir(".");
	printf("Directory contents:\n");
	if (d) {
		while ((dir=readdir(d)) != NULL){
			printf("%s\n",dir->d_name);
		}
		closedir(d);
	}


	return (0);
}
