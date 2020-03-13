#ifndef __SOCKETPARAM__
#define __SOCKETPARAM__

#include <iostream>
#include <string>


#ifdef __cplusplus
extern "C"{
#endif
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#ifdef __cplusplus
}
#endif



enum {
	socketfalse  = 0, 
	sockettrue ,
};

class socketclass {
public:
	virtual int createsocket(int domain , int type , int protocol);
	virtual int socketbind(int socket , const struct sockaddr *address , socklen_t address_len);
	virtual int socketlisten(int socket , int backlog);
	virtual int socketaccept(int socket , struct sockaddr *address , socklen_t *address_len);
	virtual int socketconnect(int sockfd , const struct sockaddr *addr , socklen_t addrlen);	
	virtual int socketshutdown(int sockfd , int flag);
	virtual bool error_info();
	template<typename Args>
	static  std::string to_string(Args args);
};



#endif
