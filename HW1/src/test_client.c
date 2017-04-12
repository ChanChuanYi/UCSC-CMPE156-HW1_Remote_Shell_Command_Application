#include <stdio.h>
#include <string.h>
#include "unp.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv){

	int	sockfd, n;
	struct sockaddr_in	servaddr;
	char buff[MAXLINE],recvline[MAXLINE+1];
	FILE *fp;

	if (argc != 3)
		err_quit("usage: a.out <IPaddress> <Port Number>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(atoi(argv[2]));	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");


	while(1){
		char buf[MAXLINE];
		printf("Please enter:\n");
		fgets(buf, MAXLINE, stdin);	//user input
		if(strcmp(buf,"exit\n")==0) break; //see if input =="exit"

		//send command to server
		Write(sockfd,buf,strlen(buf));  

		//read server response
		if((n = read(sockfd, recvline, MAXLINE))>0)  
			recvline[n] = 0;
			
		printf("%s",recvline);
			
			//locally execute command
		char path[PATH_MAX];
		fp=popen(buf,"r");		
		while (fgets(path, PATH_MAX, fp) != NULL){ 
			strncat(buff, path,strlen(path));		
		}
	   	printf("%s","----------------------\n");
	   	printf("%s",buff);

	   	//compare result
		if(strcmp(buff,recvline)==0) printf("%s","The result is valid\n");  //validate results
		
		//clear things in buff
		bzero(buff,strlen(buff));
		if(n<0)
   			err_sys("read error");
	}
	

	exit(0);


}
