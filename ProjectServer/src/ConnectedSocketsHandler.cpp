/*
 * ConnectedSocketsHandler.cpp
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#include "ConnectedSocketsHandler.h"

namespace networkingLab {

ConnectedSocketsHandler::ConnectedSocketsHandler(vector<TCPSocket*> sockVector) {
	// TODO Auto-generated constructor stub
	this->listener=new MultipleTCPSocketsListener();
	this->listener->addSockets(sockVector);

}

void ConnectedSocketsHandler::run() {

}

ConnectedSocketsHandler::~ConnectedSocketsHandler() {
	// TODO Auto-generated destructor stub
}

} /* namespace networkingLab */
