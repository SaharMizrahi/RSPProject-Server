#include<iostream>
#include<stdio.h>
#include "RSPServer.h"
using namespace std;
using namespace networkingLab;

int main() {

	RSPServer* server=new RSPServer();
	server->runServer();
	return 1;
}
