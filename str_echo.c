#include	"utils.h"
#include 	<string.h>

#define MAX 1000
#define MAXCHAR 1000

	ssize_t		n,n2;
	char		line[MAXLINE];
	
	
	char idb[MAX];
	char nameb[MAX];
	char specb[MAX];
	char t1b[MAX];
	char t2b[MAX];
	char t3b[MAX];


	// New Declare
	char pro_id[MAX];
	char prod_type[MAX];
	char brandname[MAX];
	char aQty[MAX];
	char unitPrice[MAX];
	
	//
	

	char *sp[100];

	// new declare 
	char buy[MAX]; // first buying the item
	char pay[MAX];
	char itemID[MAX];
	char item_Qty[MAX];
	char totalPrice [MAX];
	//

	char available[MAX];
	
	char confirm[MAX];
	
	
	char avid[MAX];
	char avtime[MAX];


void str_echo(int sockfd)
{
		//https://youtu.be/9KVqEpiKxTY     [To read the text file]
		FILE *fp1 = fopen("wel.txt","r");
		while(fgets(line,sizeof(line),fp1) != NULL)
		{
			n = strlen(line);
			writen(sockfd,line,n);
		
		}
		fclose(fp1);

			
	for( ; ; )
	{

		bzero(line,sizeof(line));
		if ( (n = Readline(sockfd,line, MAXLINE)) == 0)
			return;	
		
		
		sscanf(line,"%s",sp);

		
		char *characters;

		if( strcmp(sp , "blen") == 0 || strcmp(sp,"BLEN") == 0)
		{
			characters = "Blender";
			checkProType(sockfd,characters);
		}
		else if(strcmp(sp, "came") == 0  || strcmp(sp,"CAME") == 0)
		{
			characters = "Camera";
			checkProType(sockfd,characters);	
		}
		else if(strcmp(sp,"heat") == 0 || strcmp(sp,"HEAT") == 0)
		{
			characters = "Heater";
			checkProType(sockfd,characters);
		}
		
		else
		{
			bzero(line,sizeof(line));
			snprintf(line, sizeof(line),"Invalid characters ,Please try again!(example:- blen) \n");	
			n = strlen(line);
			Writen(sockfd,line,n);	
		}
	}
}




void checkProType(int sockfd,char *character)
{
	FILE *fp;
	fp = fopen("stock.txt","r");
				
	if(fp == NULL)
	{
		
		bzero(line,sizeof(line));
		snprintf(line,sizeof(line),"Item file open error\n");
		writen(sockfd,line,sizeof(line));
	}
	else
	{	
		snprintf(line,sizeof(line),"PID\tBrandName\tQty\tU.Price\n");
		n = strlen(line);
		Writen(sockfd,line,n);
		//bzero(line,sizeof(line));
			

		
		while(Fgets(line,sizeof(line),fp))
		{
			//https://youtu.be/V6CohFrRNTo     [Write & read to the buffers]									
			sscanf(line,"%s\t%s\t%s\t%s\t%s\n",&pro_id,&prod_type,&brandname,&aQty,&unitPrice);
							
			if(strcmp(prod_type,character)==0)
			{
				snprintf(line,sizeof(line),"%s\t%s\t%s\t%s\n",pro_id,brandname,aQty,unitPrice);
				n = strlen(line);
				Writen(sockfd,line,n);
						
			}
		}fclose(fp);
		
								
	}
	
	if ( (n = Readline(sockfd,line, MAXLINE)) == 0)
			return;	
			
	else if(sscanf(line,"%s %s%s%s %s",&buy,&itemID,&item_Qty)==3)
	{	
		
			
		if(strcmp(buy, "b") == 0)
		{
	
			FILE *fp;
			fp = fopen("stock.txt","r");

			if(fp == NULL)
			{
				bzero(line,sizeof(line));
				snprintf(line,sizeof(line),"item file open error\n");
				writen(sockfd,line,sizeof(line));
			}
			else
			{
				while(Fgets(line,sizeof(line),fp))
				{									
					sscanf(line,"%s\t%s\t%s\t%s\t%s\n",&pro_id,&prod_type,&brandname,&aQty,&unitPrice);
					
							

					if(strcmp(pro_id,itemID) == 0)
					 {
						 	
							purhcaseItem(sockfd,item_Qty,aQty,unitPrice,character);

					 }
					
					
				}fclose(fp);
				
			}
		}
		else
		{
			bzero(line,sizeof(line));
			snprintf(line, sizeof(line),"First character is invalid!!!!!\nPress c to continue, x to exit:\n");	
			n = strlen(line);
			Writen(sockfd,line,n);

			if ( (n = Readline(sockfd,line, MAXLINE)) == 0)
					return;	

			sscanf(line,"%s",&confirm);

			
			if(strcmp(confirm,"c") == 0 )
			{
				checkProType(sockfd,character);
			}
			else if(strcmp(confirm,"x") == 0)
			{
				err_quit("Customer:Server terminated prematurely");
			}
		}

	}				
	else
	{
		bzero(line,sizeof(line));
		snprintf(line, sizeof(line),"Please enter the values according to the correct order!\nPress c to continue, x to exit:\n");	
		n = strlen(line);
		Writen(sockfd,line,n);

		if ( (n = Readline(sockfd,line, MAXLINE)) == 0)
				return;	

		sscanf(line,"%s",&confirm); 
		if(strcmp(confirm,"c") == 0 )
		{
			checkProType(sockfd,character);
		}
		else if(strcmp(confirm,"x") == 0)
		{
			err_quit("Customer:Server terminated prematurely");
		}	
	}			
}







void purhcaseItem (int sockfd ,char *givenQty, char *currentQty, char *price , char *character)
{
	int give_Qty = atoi(givenQty);
	int cu_Qty = atoi(currentQty);
	float pr = atof(price);
	int avaQty ;
	float tot;

	char resAvailableQty[MAXLINE];
	char result[MAXLINE] ;

	
	if (give_Qty >= cu_Qty)
	{
	
		bzero(line,sizeof(line));
		snprintf(line, sizeof(line),"Given Quantitity is higher than current Quantity! \nPress c to continue, x to exit:\n");	
		n = strlen(line);
		Writen(sockfd,line,n);

		if ( (n = Readline(sockfd,line, MAXLINE)) == 0)
				return;	

		sscanf(line,"%s",&confirm); 
		if(strcmp(confirm,"c") == 0 )
		{
			checkProType(sockfd,character);
		}
		else if(strcmp(confirm,"x") == 0)
		{
			err_quit("Customer:Server terminated prematurely");
		}
	
	} 


	else {
	
	
	tot = give_Qty * pr;
	avaQty = cu_Qty - give_Qty;


	printf("**** Available Quantity:-  %d ******",avaQty);
	
	sprintf(result,"Total Price: %.2f . Press “P” to confirm the order. \n",tot);
	
	snprintf(line,sizeof(line),"%s",result);
	n = strlen(line);
	Writen(sockfd,line,n);

	sprintf(resAvailableQty,"%d",avaQty);


	confirmPurchase(sockfd,resAvailableQty,currentQty,character);


	}

	

}



void confirmPurchase (int sockfd ,char *aVQty, char *currentQty,char *character)
{
	

	if ( (n = Readline(sockfd,line, MAXLINE)) == 0)
			return;	
			
	else if(sscanf(line,"%s %s%s%s %s",&pay,&itemID,&item_Qty)==3)
	{

		if(strcmp(pay,"p") == 0)
		{

			FILE *fp;
			fp = fopen("stock.txt","r");

			if(fp == NULL)
			{
				bzero(line,sizeof(line));
				snprintf(line,sizeof(line),"stock file open error\n");
				writen(sockfd,line,sizeof(line));
			}

			else 
			{
					char datab[100][1000];
					bzero(datab,sizeof(datab));
					bzero(line,sizeof(line));
					int x = 0;
					while(Fgets(line,sizeof(line),fp)!=NULL)
					{
						sscanf(line,"%s\t%s\t%s\t%s\t%s\n",&pro_id,&prod_type,&brandname,&aQty,&unitPrice);


						if(strcmp(pro_id,itemID) == 0)
					 {
						 if(strcmp(aQty ,currentQty) == 0 )
							{
								
								for(int i ; i < 10 ; i++)
								{ aQty[i]= aVQty[i] ; }
 

								char *update = &aQty; 
														
						
								snprintf(line,sizeof(line),"%s\t%s\t%s\t%s\t%s",pro_id,prod_type,brandname,update,unitPrice);
								n = strlen(line);
								strncpy(datab[x],line,n);
								x++;
								continue;
							}

								

					 }

					 	snprintf(line,sizeof(line),"%s\t%s\t%s\t%s\t%s",pro_id,prod_type,brandname,aQty,unitPrice);
						n = strlen(line);
						strncpy(datab[x],line,n);
						x++;

					}


					fclose(fp);
					FILE *fp2 = fopen("stock.txt","w");
					for(int i=0;i<11;i++)
					{
						fprintf(fp2,"%s\n",datab[i]);	
						
					}fclose(fp2);
					snprintf(line,sizeof(line),"Your order processed successfully!\n");
					n = strlen(line);
					Writen(sockfd,line,n);
					char database[MAXLINE];
					snprintf(database,sizeof(database),"Database updated successfully!\n");
					Fputs(database,stdout);
					



			}
					

		}

		else {

			snprintf(line,sizeof(line),"First character is invalid!\n");
			n = strlen(line);
			Writen(sockfd,line,n);
			checkProType(sockfd,character);


		}



	}
	






}








			
					


