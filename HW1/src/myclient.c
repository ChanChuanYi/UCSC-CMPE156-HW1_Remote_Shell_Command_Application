#include	"unp.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int
main(int argc, char **argv)
{
	int					sockfd, n;
	
	struct sockaddr_in	servaddr;
	char test[]="exit\n",recvline[MAXLINE+1],buf[MAXLINE];
	
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
		printf("Please enter:\n");

		//capture user input
		
		fgets(buf, MAXLINE, stdin);
		if(strcmp(buf,test)==0) break;

		//send command to server
		Write(sockfd,buf,strlen(buf));
	
		//read server response
		if((n = read(sockfd, recvline, MAXLINE))>0)
			recvline[n] = 0;
			if (fputs(recvline, stdout) == EOF)
			 	err_sys("fputs error");
		
		if(n<0)
   			err_sys("read error");
	}
	

	exit(0);
}
