#include "socketpar.h"

using namespace std;


template<typename Args>
 std::string socketclass::to_string(Args args)
{
	std::string str;
	std::ostringstream ostring;
	ostring << args;
//	return ostring.str();	
	return str;
}


bool socketclass::error_info()
{
	#ifdef DEBUG
	std::string str;
	perror("error failed!\n");
	//str = socketclass::to_string("error num" , errno);
	str = "error num" + errno;
	std::cout << str << std::endl;
	#endif
	return sockettrue;
}

int socketclass::createsocket(int domain , int type , int protocol)
{

	int sock ;
	sock = socket(domain , type , protocol);
	if(sock < 0)
	{
		error_info();
	}

	return sock;

}
int socketclass::socketbind(int socket , const struct sockaddr *address , socklen_t address_len)
{
	
	int err;
	err = bind(socket , address , address_len);
	if(err)
	{	
		error_info();
		return socketfalse;
	}
	return sockettrue;

}


int socketclass::socketlisten(int socket , int backlog)
{
	int err;
	err = listen(socket , backlog);
	if(err)
	{
		error_info();
		return socketfalse;
	}
	return sockettrue;

}


int socketclass::socketaccept(int socket , struct sockaddr * address , socklen_t * address_len)
{
	int socketcli;
	socketcli = accept(socket , address , address_len);
	if(socketcli < 0)
	{
		error_info();
	}
	return socketcli;

}

int socketclass::socketconnect(int sockfd , const struct sockaddr *addr , socklen_t addrlen)
{
	int err;
	err = connect(sockfd , addr, addrlen);
	if(err)
	{
		error_info();
		return socketfalse;
	}	
	return sockettrue;

      
                                                                                                         
}


int socketclass::socketshutdown(int sockfd , int flag)
{
	int err;
	err = shutdown(sockfd , flag);
	if(err)
	{
		error_info();
		return socketfalse;
	}

	return sockettrue;

}
