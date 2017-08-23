#include <Protocol.h>
#include<iostream>
#include<stdio.h>
#include "RSPGameClient.h"
#include "RSPGameServer.h"
#define IP "127.0.0.1"
using namespace std;
using namespace networkingLab;

int main() {
	RSPGameServer*  server=new RSPGameServer(SERVER_PORT);
	server->start();
	/*sleep(2);
	RSPGameClient* client=new RSPGameClient("sahar","sahar","login");
	client->start();*/
	sleep(1000);







	return 1;
}
