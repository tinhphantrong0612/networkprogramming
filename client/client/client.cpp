// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stream.h"

void update();
void render();

int main(int argc, char* argv[])
{
	//Get port number and address
	int port_number = atoi(argv[2]);
	char* ip_address = argv[1];

	//Initialize WSA
	initWSA();
	
	//Create client socket
	Socket client(port_number, ip_address);
	client.set_timeout(5000); // Timeout 5s
	if (client.connect_to_server()) {
		return 1;
	}


	printf("Client started!!\n");
	bool running = true;
	//Game loop
	while (running) {
		update();
		render();
	}

	//End
	WSACleanup();
	return 0;
}

void update() {

}

void render() {

}
