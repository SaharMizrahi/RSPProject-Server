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

using namespace std;
namespace networkingLab {

class LoginHandler : public MThread{

	bool stopFlag;
	vector<TCPSocket*>* socketVector;
	TCPSocket* socket;
	int checkUser(char * username,char* password);
public:
	void stop();
	virtual void run();
	LoginHandler(TCPSocket* listeningSocket,vector<TCPSocket*>* Vector);
	virtual ~LoginHandler();
};

} /* namespace networkingLab */

#endif /* SRC_LOGINHANDLER_H_ */
