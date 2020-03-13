#include "socketserver.h"





int main(int argc , char *argv[])
{
	unsigned short portnum;
	const char *ipaddr;
	unsigned short socknum;
	if(argc < 4)
	{
		std::cout << "param low" << std::endl;
		exit(-1);
	}

	ipaddr = argv[1]; /**first param is ipaddr**/
	portnum = strtol(argv[2] , NULL , 10); /**second param is portnum**/
	socknum = strtol(argv[3] , NULL , 10); /**third param is  socknum**/
	
	socketserverclass server(ipaddr , portnum , socknum);
	server.createmaster();
	
	exit(0);
}
