/*
 * ConnectedSocketsHandler.cpp
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#include "ConnectedSocketsHandler.h"
#include <fstream>
#include <string.h>
#include "RSPUser.h"
#include <stdlib.h>     /* srand, rand */

namespace networkingLab {

ConnectedSocketsHandler::ConnectedSocketsHandler() {
	// TODO Auto-generated constructor stub
	this->listener=new MultipleTCPSocketsListener();
	this->listener->addSockets(this->serverSockets);
	this->stop=true;
}

void ConnectedSocketsHandler::run() {
	this->stop=false;
	TCPSocket* sock;
	while(!stop&&(sock=this->listener->listenToSocket())!=NULL)
	{
		int size;
		char buffer[100];
		sock->read((char*)&size, 4);
		sock->read(buffer, ntohl(size));
		cout<<"new msg: "<<buffer<<endl;

	}


}

void ConnectedSocketsHandler::addClient(char* username, TCPSocket* socket) {
	int rank=0;
	ifstream in ("src/rank.txt");
	if(in.is_open())
	{
		string line;
		while(getline(in,line)&&strcmp(line.c_str(),"")!=0)
		{
			const char* s=line.c_str();
			char* str=new char[line.length()+1];
			strcpy(str,s);
			char* u=strtok(str," ");
			char* r=strtok(NULL," ");
			if(strcmp(u,username)==0)
			{
				rank=atoi(r);

				break;
			}
		}

	}
	int random=rand()%100+1;
	int newPort=random+socket->getPort();
	int netPort=htonl(newPort);
	socket->write((char*)&netPort, 4);
	socket=new TCPSocket(newPort);
	TCPSocket* ready=socket->listenAndAccept();
	RSPUser* newUser=new RSPUser(username,rank,ready,newPort);
	this->usersVector.push_back(newUser);
	this->stop=true;
	this->listener->addSocket(ready);
	this->start();
}

ConnectedSocketsHandler::~ConnectedSocketsHandler() {
	// TODO Auto-generated destructor stub
}

} /* namespace networkingLab */
