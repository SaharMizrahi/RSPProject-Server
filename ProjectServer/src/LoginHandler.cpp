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
	TCPSocket* readySock;
	while(!stopFlag&&(readySock=socket->listenAndAccept())!=NULL)
	{
		//read msg from new client
		readySock->read((char*)&size, 4);
		readySock->read(buffer,ntohl(size));
		//define if it's login or register
		char* cmd=strtok(buffer," ");
		//get details
		char* username=strtok(NULL," ");
		char* password=strtok(NULL," ");
		if(strcmp(cmd,"login")!=0&&strcmp(cmd,"register")!=0)
		{
			char* msg1="-1";
			int size=htonl(sizeof(msg1));
			readySock->write((char*)&size, 4);
			readySock->write(msg1, size);
		}
		else
		{
			int res=checkUser(cmd, username, password);
			cout<<"result: "<<res<<endl;

		}


	}
	//waiting for new client to connect
	/*do{
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
	}while(!stopFlag);*/
}

LoginHandler::LoginHandler(TCPSocket* listeningSocket,vector<TCPSocket*>* Vector) {
	socket=listeningSocket;
	socketVector=Vector;
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
				return 3;



			}
			else
			{
				return -2;
			}

		}



	}
	cout<<"checkdadsda"<<endl;

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
