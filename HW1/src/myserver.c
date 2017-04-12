
#include	<time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
int main(int argc, char **argv)
{
	int					listenfd, connfd,n;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE],recvline[MAXLINE+1],path[MAXLINE];
	FILE *fp;
	
	
	extern FILE *popen();

	if(argc !=2)
		err_quit("usage: a.out <Port Number>");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[1]));
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	
	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		
		//Read and Write Loop Start----
		while ( (n = read(connfd, recvline, MAXLINE)) > 0){
			recvline[n] = 0;//null terminate 
			

			//execute bash command
			fp = popen(recvline,"r");			
			if (fp == NULL) {
				Write(connfd,"no such command",15);
			}

			//retrieve response
			 while (fgets(path, PATH_MAX, fp) != NULL){
     			strncat(buff, path,strlen(path));
     			
     		}
     		printf("%s",buff);
     		Write(connfd,buff,strlen(buff));
     		bzero(buff,strlen(buff));
    		pclose(fp);
		}
		//Read and Write Loop Ends
		printf("%s\n","connection ended");
		Close(connfd);
	}
}
