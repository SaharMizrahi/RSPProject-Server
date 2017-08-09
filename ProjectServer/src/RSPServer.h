/*
 * RSPServer.h
 *
 *  Created on: Aug 9, 2017
 *      Author: user
 */

#ifndef SRC_RSPSERVER_H_
#define SRC_RSPSERVER_H_
#define PORT 9999
#include<iostream>
#include<stdio.h>
#include "TCPSocket.h"
#include <pthread.h>
#include "MThread.h"
#include "LoginHandler.h"
#include <vector>
using namespace std;
namespace networkingLab {


class RSPServer {
private:
	LoginHandler *lh;
	vector<TCPSocket*>* usersVector;

public:
	void runServer();
	RSPServer();
	virtual ~RSPServer();
};


} /* namespace networkingLab */

#endif /* SRC_RSPSERVER_H_ */
