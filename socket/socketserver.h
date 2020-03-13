#ifndef __SOCKETSERVER__
#define __SOCKETSERVER__



#include <iostream>
#include <string>
#include "socketpar.h"

#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#ifdef __cplusplus
}
#endif


#define SERVERIPADDRESS "192.168.190.111"
#define PORTNUM        8888

typedef struct serverstr{
	int serversock;
	int *clientsock;
	int num;
	pthread_t *pid;
	struct sockaddr_in *address;

}SER_T;


typedef struct sockaddr_in sockaddr_t;
class socketserverclass : public socketclass{

public:
	socketserverclass(const char *ipaddr_param , unsigned short portnum_param,int sonnum);
	~socketserverclass();
	int createmaster(void);
	static void * socketpthread_fun(void *args);

private:
//	pthread_t *pid;
	SER_T serv;
	int socknum;
//	void socketlistenthread(void *argv);
	char ipaddr[100];
	unsigned short portnum;
	
};







#endif
