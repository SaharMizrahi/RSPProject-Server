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
		cout<<"new client connected"<<endl;
		bool isAuthentic=false;
		int chances=0;

		//read username and password
		readySocket->read((char*)&size, 4);
		readySocket->read(buffer,ntohl(size));
		char* username=strtok(buffer," ");
		char* password=strtok(NULL," ");
		int checkResult=checkUser(username, password);
		cout<<"check:"<<checkResult<<endl;
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
	ifstream in ("src/users.txt");

	string line;
	if(in.is_open())
	{
		while(getline(in,line))
		{
			const char* s=line.c_str();
			char* str=new char[line.length()+1];
			strcpy(str,s);
			char* username=strtok(str," ");
			char* password=strtok(NULL," ");
			cout<<"username: "<<username<<" pass: "<<password<<endl;
		}

		in.close();
		return 2;
	}
	else
		return 1;
	/*string line;
	ifstream in ("/files/users.txt");
	in.open("/files/users.txt");
	if(in.is_open())
	{
	//check if username exist
	while(in.good())//while not end of file
	{
		getline(in,line);
		cout<<"line: "<<line<<endl;
		sleep(5);
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
	ofstream out ("/files/users.txt");
	out.open("/files/users.txt");
	out<<username<<" "<<password<<" ";
	out.close();
	}
	 */

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
