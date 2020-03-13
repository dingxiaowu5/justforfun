#include "socketclient.h"


clientsocketclass::clientsocketclass(const char *ipaddr_param , unsigned short portnum_param)
{
	bzero(ipaddr , 100);
	strcpy(ipaddr , ipaddr_param);
	portnum = portnum_param;

}
int clientsocketclass::createclient(void)
{

	pthread_t pid;
	struct sockaddr_in sockaddr;
	
	clisocket =createsocket(AF_INET , SOCK_STREAM , 0);
	if(clisocket < 0)
	{
		return -1;
	} 
	
	bzero(&sockaddr , sizeof(sockaddr));	
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(portnum);
	inet_pton(AF_INET, ipaddr , &sockaddr.sin_addr);
	
	while(socketconnect(clisocket , (const struct sockaddr *)&sockaddr , sizeof(sockaddr)) != 0);
	
	if(pthread_create(&pid , NULL , clientsocketclass::clientpthread_fun , &clisocket) !=0)
	{
		close(clisocket);
		return -1;
	}

	if(pthread_join(pid, NULL)!=0)
	{
		std::cout <<"wait the pthread failed!" <<std::endl;
	}

		
	close(clisocket);
	return 0;
}


void *clientsocketclass::clientpthread_fun(void *argv)
{
	char str[100];
	int clisock = *(int *)argv;
	while(1)
	{
		bzero(str , 100);
		if(read(0, str, 100) > 0)
		{
			std::cout << "client send " << str<< std::endl;
			if(send(clisock , str , strlen(str),0) > 0)
			{
				bzero(str , 100);
				if(read(clisock , str ,100) > 0)
				{
					std::cout << "get the server:" << str << std::endl;
				}
			}
			
		}
	}

}
