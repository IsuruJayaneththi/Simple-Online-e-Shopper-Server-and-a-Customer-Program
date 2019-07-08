#include	"utils.h"
#include 	"signal.c"
#include	"sigchldwaitpid.c"

int main(int argc, char **argv)
{
	int			listenfd, connfd;
	pid_t			childpid;
	socklen_t		clilen;
	struct sockaddr_in	cliaddr, servaddr;
	char			*cli_ip;

	char			buff[MAXLINE];

	
	
	

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_TCP_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    	Listen(listenfd,LISTENQ);
  	
	
	//Handling Zombie process
	signal(SIGCHLD,sig_chld);  //function is in sigchldwaitpid.c file

	for ( ; ; ) 
   	{
		//Handling slow systemcall (EINTER)
		clilen = sizeof(cliaddr);
       	 	if((connfd = Accept(listenfd, (SA *) &cliaddr, &clilen))<0)
		{
			if(errno == EINTR)
			continue;

			else
			err_sys("Accept Error");
		}
		
		//cli_ip=inet_ntop(AF_INET,&cliaddr.sin_addr,buff,sizeof(buff));
		cli_ip=inet_ntoa(cliaddr.sin_addr);
		printf("Connection from %s, port %d\n",cli_ip,ntohs(cliaddr.sin_port));	

		
		if((childpid=fork())==0)
		{
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}		
        	close(connfd);
    }
}







