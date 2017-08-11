/*
 * ConnectedSocketsHandler.h
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#ifndef CONNECTEDSOCKETSHANDLER_H_
#define CONNECTEDSOCKETSHANDLER_H_
#include "MThread.h"
#include<iostream>
#include<stdio.h>
#include <vector>
#include "MultipleTCPSocketsListener.h"
#include "TCPSocket.h"
using namespace std;
namespace networkingLab {

class ConnectedSocketsHandler : public MThread {
private :
	MultipleTCPSocketsListener* listener;
public:
	void run();
	ConnectedSocketsHandler(vector<TCPSocket*> sockVector);
	virtual ~ConnectedSocketsHandler();

};

} /* namespace networkingLab */

#endif /* CONNECTEDSOCKETSHANDLER_H_ */
