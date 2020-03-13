#include "socketserver.h"
#include <arpa/inet.h>
#include <unistd.h>

static void* socketpthread_fun(void *argv);
socketserverclass::socketserverclass(const char *ipaddr_param , unsigned short portnum_param , int sonnum):socketclass()
{
	serv.pid = new pthread_t[sonnum];
	serv.address = new sockaddr_t[sonnum];
	serv.serversock = 0;
	serv.clientsock = new int[sonnum];
	serv.num = 0;
	memset(ipaddr , 0 , sizeof(char)*100);
	strcpy(ipaddr , ipaddr_param);
	portnum = portnum_param;
	socknum = sonnum;
}

socketserverclass::~socketserverclass()
{
	delete[] serv.pid;
	delete[] serv.address;
	delete[] serv.clientsock;
}


int socketserverclass::createmaster(void)
{
	int err;
	int socket;
	struct sockaddr_in sockaddr;
	socklen_t socklen;
	pthread_t pid;
	char dst[100];
	if((socket = createsocket(AF_INET , SOCK_STREAM , 0)) < 0)
	{
		return -1;
	}
	std::cout <<"get the info:"<< portnum << " " << ipaddr << " " <<socket<<" "<<socknum<<std::endl;
	serv.serversock  = socket;
	bzero(&sockaddr , sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(portnum);
	inet_pton(AF_INET , ipaddr , &sockaddr.sin_addr);
		
	bzero(dst , 100);
	inet_ntop(AF_INET ,&sockaddr.sin_addr ,dst,INET6_ADDRSTRLEN);		
	std::cout << "get ip addr :" << dst << std::endl;
	if(socketbind(serv.serversock , (const struct sockaddr *)&sockaddr , sizeof(sockaddr))<0)
	{
		close(socket);
		return -1;
	}

	if(socketlisten(serv.serversock ,socknum) < 0)
	{
		close(socket);
		return -1;
}	
	
	for(int i = 0 ; i < socknum ; i++)
	{
		bzero(&sockaddr , sizeof(sockaddr));
		std::cout << "enter info"<<std::endl;
		socket = socketaccept(serv.serversock ,(struct sockaddr *)&sockaddr , &socklen);
		std::cout << "accept get" << std::endl;
		if(socket > 0)
		{
			if(pthread_create(&pid , NULL , socketserverclass::socketpthread_fun , &socket) == 0)
			{
				serv.num += 1;
				serv.pid[i] = pid;
				serv.clientsock[i] = socket;
				serv.address[i].sin_port = ntohs(sockaddr.sin_port);
				serv.address[i].sin_addr = sockaddr.sin_addr;	
			}
			
		}			
	}
	

	for(int i = 0 ; i < serv.num ; i++)
	{
		if(pthread_join(serv.pid[i] , NULL) != 0)
		{
			perror("pthread id join failed!");
		}
	}
	close(serv.serversock);
	return 0;


}

void* socketserverclass::socketpthread_fun(void *argv)
{
	char str[100];
	if(argv == NULL)
	{
		std::cout << "input param error"<<std::endl;
		pthread_exit(0);
	}
	int socket = *(int *)argv;
	
	while(1)
	{
		bzero(str , 100);
		if(read(socket , str , 100-1) > 0)
		{
			std::cout << str << std::endl;
			if(strcmp(str , "socket exit") == 0)
			{
				pthread_exit(0);
			}
			bzero(str , 100);
			strcpy(str , "server receive!");
			if(send(socket ,str , strlen(str) , 0) <= 0)
			{
				send(socket ,str , strlen(str) , 0);
			}
		}
	}
	close(socket);	
	pthread_exit(0);
}
