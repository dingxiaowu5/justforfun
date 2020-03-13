#ifndef __CLIENTSOCKET__
#define __CLIENTSOCKET__
#include "socketpar.h"
#include <pthread.h>
#ifdef __cpluscplus
extern "C"{
#endif
#include <string.h>

#ifdef __cpluscplus
}
#endif
class clientsocketclass : public socketclass{
public:
	clientsocketclass(const char *ipaddr_param , unsigned short portnum_param);
	int createclient(void);
	static void * clientpthread_fun(void *argv);




private:
	unsigned short portnum;
	char ipaddr[100];
	int clisocket;
	pthread_t pid;

};




#endif
