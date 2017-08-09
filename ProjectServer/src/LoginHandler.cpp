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
namespace networkingLab {



void LoginHandler::run() {
	this->stopFlag=false;
	char * userAuth=(char*)"access is valid, welcome to RSP server";
	int userAuthSize=htonl(sizeof(userAuth));
	char * userFaild=(char*)"somthing is wrong, connect and try again...bye bye";
	int userFaildSize=htonl(sizeof(userFaild));
	char* userReg=(char*)"new user has registered";
	int userRegSize=htonl(sizeof(userReg));
	char buffer[100]={0};
	int size;
	//waiting for new client to connect

	do{
	TCPSocket* readySocket=this->socket->listenAndAccept();
	//Authenticate client
	if(readySocket!=NULL)
	{
		bool isAuthentic=false;
		int chances=0;

		//read username and password
		readySocket->read((char*)&size, 4);
		readySocket->read(buffer,ntohl(size));
		int i=0;
		while(buffer[i]!=' '||buffer[i]!='\0')//get username
		{
			i++;
		}
		char* username=strncpy(username,buffer,i);
		int j=i+2;
		while(buffer[j]!=' '||buffer[j]!='\0')//get password
		{
			j++;
		}
		char* password=strncpy(password,buffer+i+1,j);
		int checkResult=checkUser(username, password);
		switch (checkResult)
		{
		case 0://username+password is valid
			readySocket->write((char*)&userAuthSize, 4);
			readySocket->write(userAuth, userAuthSize);
			socketVector->push_back(readySocket);
			break;
		case 1://password don't match to username
			readySocket->write((char*)&userFaildSize, 4);
			readySocket->write(userFaild, userFaildSize);
			sleep(2);
			readySocket->close();
			break;
		case 2://registerd new user in new username and password
			readySocket->write((char*)&userRegSize, 4);
			readySocket->write(userReg, userRegSize);
			socketVector->push_back(readySocket);
			break;

		}

	}
	}while(!stopFlag);
}

LoginHandler::LoginHandler(TCPSocket* listeningSocket,vector<TCPSocket*>* Vector) {
	socket=listeningSocket;
	socketVector=Vector;
	this->stopFlag=true;

}

int LoginHandler::checkUser(char* username, char* password) {
	string line;

	in.open("/files/users.txt");
	//check if username exist
	while(!in.eof())//while not end of file
	{
		in>>line;
		if(strcmp(username,line.c_str())==0)//we found the username
		{
			in>>line;//read the username's password
			if(strcmp(password,line.c_str())==0)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			in>>line;//reading the non-matching username's password
		}
	}
	in.close();
	//if not exist,add username+password to file
	out.open("/files/users.txt");
	out<<username<<" "<<password<<" ";
	out.close();

	return 2;
}

void LoginHandler::stop() {
	this->stopFlag=true;
	this->waitForThread();
}

LoginHandler::~LoginHandler() {
	// TODO Auto-generated destructor stub

}

} /* namespace networkingLab */
