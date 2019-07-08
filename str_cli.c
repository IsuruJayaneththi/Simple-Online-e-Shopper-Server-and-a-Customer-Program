#include	"utils.h"

void
str_cli(FILE *fp, int sockfd)
{
	int 	maxfd;
	fd_set	rset,wset;
	char	sendline[MAXLINE], recvline[MAXLINE];
	int 	count,n;


	FD_ZERO(&rset);

	for( ; ; )
	{
		FD_SET(fileno(fp),&rset);
		FD_SET(sockfd,&rset);
		maxfd = max(fileno(fp), sockfd) + 1;
		

		select(maxfd,&rset,NULL,NULL,NULL);

		bzero(sendline,sizeof(sendline));
		bzero(recvline,sizeof(recvline));
		
		if(FD_ISSET(sockfd,&rset))
		{
			if(read(sockfd,recvline,MAXLINE) == 0)
			{
				err_quit("Customer !! : Server terminated prematurely");
			}
			else
			{
				Fputs(recvline,stdout);
				
			}
		}

		
		 if(FD_ISSET(fileno(fp),&rset))
		{
			if(Fgets(sendline,MAXLINE,fp) ==NULL)
			{
				return;
			}
			else
			{
				//Fputs(sendline,stdout);
				writen(sockfd,sendline,strlen(sendline));
			}
		}
	}		
}
