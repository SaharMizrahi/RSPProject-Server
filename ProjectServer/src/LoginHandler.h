/*
 * LoginHandler.h
 *
 *  Created on: Aug 9, 2017
 *      Author: user
 */

#ifndef SRC_LOGINHANDLER_H_
#define SRC_LOGINHANDLER_H_
#include "MThread.h"
#include<iostream>
#include<stdio.h>
#include <vector>
#include "TCPSocket.h"
#include "File.h"
#include <iostream>
#include <fstream>
/**
 * PROTOCOL:
 * -2 can't open file
 * -1 wrong command
 * 0 login request approved
 * 1 login-password mistake
 * 2 login-username not exist
 * 3 register request approved
 * 4 register-username already exist
 */
using namespace std;
namespace networkingLab {

class LoginHandler : public MThread{

	bool stopFlag;
	vector<TCPSocket*>* socketVector;
	TCPSocket* socket;
	int checkUser(char* cmd,char * username,char* password);
public:
	void stop();
	virtual void run();
	LoginHandler(TCPSocket* listeningSocket,vector<TCPSocket*>* Vector);
	virtual ~LoginHandler();
};

} /* namespace networkingLab */

#endif /* SRC_LOGINHANDLER_H_ */
