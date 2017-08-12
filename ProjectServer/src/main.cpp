#include<iostream>
#include<stdio.h>
#include "RSPServer.h"
#define PORT 6017
#define IP "127.0.0.1"
using namespace std;
using namespace networkingLab;

int main() {

	RSPServer* server=new RSPServer(PORT);
	server->runServer();
	TCPSocket* s=new TCPSocket(IP,PORT);
	char buffer[]="login sahar sahar";
	int size=htonl(sizeof(buffer));
	s->write((char*)&size, 4);
	s->write(buffer, size);
	int serverAnswer;
	s->read((char*)&serverAnswer, 4);
	switch(ntohl(serverAnswer))
	{
	case 0:
	case 3:
		int newPort;
		s->read((char*)&newPort, 4);
		sleep(2);
		s=new TCPSocket(IP,ntohl(newPort));

		char buf[]="testing ConnectedSocketsListener";
		int bufSize=htonl(sizeof(buf));
		s->write((char*)&bufSize, 4);
		s->write(buf, bufSize);
		sleep(4);
		s->close();
		break;


	}





	return 1;
}
