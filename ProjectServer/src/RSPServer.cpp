/*
 * RSPServer.cpp
 *
 *  Created on: Aug 9, 2017
 *      Author: user
 */

#include "RSPServer.h"
#include "LoginHandler.h"
namespace networkingLab {

RSPServer::RSPServer() {
	// TODO Auto-generated constructor stub

}

void RSPServer::runServer() {
	TCPSocket* loginSocket=new TCPSocket(PORT);
	lh=new LoginHandler(loginSocket,this->usersVector);
	lh->start();

}

RSPServer::~RSPServer() {
	// TODO Auto-generated destructor stub
	lh->stop();
}

} /* namespace networkingLab */
