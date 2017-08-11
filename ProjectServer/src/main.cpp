#include<iostream>
#include<stdio.h>
#include "RSPServer.h"
#define PORT 6461
#define IP "127.0.0.1"
using namespace std;
using namespace networkingLab;

int main() {

	RSPServer* server=new RSPServer(PORT);
	server->runServer();
	TCPSocket* s=new TCPSocket(IP,PORT);
	char buffer[]="sahar sahar";
	int size=htonl(sizeof(buffer));
	s->write((char*)&size, 4);
	s->write(buffer, size);
	sleep(10);
	s->close();
	return 1;
}
