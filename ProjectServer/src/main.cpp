#include <Protocol.h>
#include<iostream>
#include<stdio.h>
#include "TCPSocket.h"
#include "RSPGameClient.h"
#include "RSPGameServer.h"
#include "MThread.h"
#define IP "127.0.0.1"
#include "Encryptor.h"
using namespace std;
using namespace networkingLab;

int main() {


	RSPGameServer* server=new RSPGameServer(SERVER_PORT);
	server->start();
	sleep(1);
	RSPGameClient *client1=new RSPGameClient("gal","gal");
	client1->start();
	sleep(10);
	RSPGameClient *client2=new RSPGameClient("sahar","sahar");
	client2->start();
	client1->waitForThread();

	/*Encryptor* e=new Encryptor();

	cout<<e->encrypt("gal")<<endl;
	cout<<e->encrypt("sahar")<<endl;
	cout<<e->encrypt("gal")<<endl;*/








	return 1;
}
