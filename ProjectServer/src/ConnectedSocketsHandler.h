/*
 * ConnectedSocketsHandler.h
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#ifndef CONNECTEDSOCKETSHANDLER_H_
#define CONNECTEDSOCKETSHANDLER_H_
#include "MThread.h"
#include "RSPUser.h"
#include<iostream>
#include<stdio.h>
#include <vector>
#include "MultipleTCPSocketsListener.h"
#include "TCPSocket.h"
using namespace std;
namespace networkingLab {

class ConnectedSocketsHandler : public MThread {
private :
	bool stop;
	MultipleTCPSocketsListener* listener;
	vector<TCPSocket*> serverSockets;
	vector<RSPUser*> usersVector;
public:
	void addClient(char * username,TCPSocket* socket);
	void run();
	ConnectedSocketsHandler();
	virtual ~ConnectedSocketsHandler();

};

} /* namespace networkingLab */

#endif /* CONNECTEDSOCKETSHANDLER_H_ */
