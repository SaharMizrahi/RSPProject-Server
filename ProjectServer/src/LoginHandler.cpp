/*
 * LoginHandler.cpp
 *
 *  Created on: Aug 9, 2017
 *      Author: user
 */

#include "LoginHandler.h"
#include<string.h>
#include <fstream>
#include <iostream>
#include "File.h"

namespace networkingLab {


void LoginHandler::handleClient(TCPSocket* sock) {
	if(sock!=NULL)
	{
		int size;
		char buffer[100];
		//read msg from new client
		sock->read((char*)&size, 4);
		sock->read(buffer,ntohl(size));
		//define if it's login or register
		char* cmd=strtok(buffer," ");
		//get details
		char* username=strtok(NULL," ");
		char* password=strtok(NULL," ");
		if(strcmp(cmd,"login")!=0&&strcmp(cmd,"register")!=0)
		{
			char* msg1="-1";
			int size=htonl(sizeof(msg1));
			sock->write((char*)&size, 4);
			sock->write(msg1, size);
		}
		else
		{
			int res=checkUser(cmd, username, password);
			int netRes=htonl(res);
			sock->write((char*)&netRes, 4);
			switch(res)
			{
				case 0://success login
				case 3://success register
					this->sockesHandler->addClient(username, sock);
					break;
				case -1:
				case 1:
				case 2:
				case 4:
					sock->close();
					break;
			}
		}
	}
}
void LoginHandler::run() {
	this->stopFlag=false;
	TCPSocket* readySock;
	while(!stopFlag&&(readySock=socket->listenAndAccept())!=NULL)
	{
		this->handleClient(readySock);



	}

}

LoginHandler::LoginHandler(TCPSocket* listeningSocket,ConnectedSocketsHandler** sh) {
	socket=listeningSocket;
	this->sockesHandler=*sh;
	this->stopFlag=true;

}

int LoginHandler::checkUser(char* cmd,char* username, char* password) {


	ifstream in("src/users.txt");
	string line;
	if(in.is_open())
	{

		if(strcmp(cmd,"login")==0)
		{
			while(getline(in,line)&&strcmp(line.c_str(),"")!=0)
			{


				const char* s=line.c_str();
				char* str=new char[line.length()+1];
				strcpy(str,s);
				char* u=strtok(str," ");
				char* p=strtok(NULL," ");
				if(strcmp(u,username)==0)
				{
					if(strcmp(p,password)==0)
					{
						in.close();
						return 0;
					}
					else
					{
						in.close();
						return 1;
					}
				}


			}
			return 2;
		}
		else if(strcmp(cmd,"register")==0)
		{

			while(getline(in,line)&&strcmp(line.c_str(),"")!=0)
			{
				const char* s=line.c_str();
				char* str=new char[line.length()+1];
				strcpy(str,s);
				char* u=strtok(str," ");
				char* p=strtok(NULL," ");
				if(strcmp(u,username)==0)
				{
					return 4;
				}

			}



			if(in.is_open())
			{
				in.close();
				char buffer[100];
				strcat(buffer,username);
				strcat(buffer," ");
				strcat(buffer,password);
				ofstream out ("src/users.txt");
				out.write(buffer,sizeof(buffer));
				out.close();
				ofstream rankOut ("src/rank.txt");
				char b[100];
				strcat(b,username);
				strcat(b," ");
				strcat(b,"0");
				rankOut.write(b,sizeof(b));
				rankOut.close();
				return 3;



			}
			else
			{
				return -2;
			}

		}



	}

	return -2;


}

void LoginHandler::stop() {
	this->stopFlag=true;
	this->waitForThread();
}



LoginHandler::~LoginHandler() {
	// TODO Auto-generated destructor stub
this->socket->close();
}

} /* namespace networkingLab */
