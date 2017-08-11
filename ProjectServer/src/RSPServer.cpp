/*
 * RSPServer.cpp
 *
 *  Created on: Aug 9, 2017
 *      Author: user
 */

#include "RSPServer.h"
#include "LoginHandler.h"
namespace networkingLab {

RSPServer::RSPServer(int port) {
	// TODO Auto-generated constructor stub
	 this->port=port;

}

void RSPServer::runServer() {

	TCPSocket* loginSocket=new TCPSocket(this->port);
	lh=new LoginHandler(loginSocket,&this->usersVector);
	lh->start();
	sleep(2);

	//this->sh=new ConnectedSocketsHandler(this->usersVector);
}

RSPServer::~RSPServer() {
	// TODO Auto-generated destructor stub
	lh->stop();

}

} /* namespace networkingLab */
