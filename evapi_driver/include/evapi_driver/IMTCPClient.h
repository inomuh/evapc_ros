#ifndef INCLUDE_IMTCPCLIENT_H_
#define INCLUDE_IMTCPCLIENT_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>


#include <vector>
#include <iostream>



using namespace std;

class IMTCPClient
{
public:
	IMTCPClient();
	IMTCPClient(string str_server, int i_port_no);
	~IMTCPClient();
		
	int Read(char * p_c_buffer, int i_size);
	int Write(char * p_c_data, int i_size);
		
	
private:

	int Connect();
	void Disconnect();

	int i_port_no;
	int i_sd;
	
	string str_server;
	

};

#endif
