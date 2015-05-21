#include "evapi_driver/IMTCPClient.h"

IMTCPClient::IMTCPClient()
{
	this->i_port_no = 9090;
	this->i_sd = -1;
	this->str_server = "evarobotDSK";
	this->Connect();
}

IMTCPClient::IMTCPClient(string str_server, int i_port_no)
{
	this->i_port_no = i_port_no;
	this->i_sd = -1;
	this->str_server = str_server;
	this->Connect();
}


IMTCPClient::~IMTCPClient()
{
	this->Disconnect();
}


int IMTCPClient::Connect()
{
	struct hostent *hostp;
	int i_status_value = -1;
	struct sockaddr_in server_address;
	
	/* get a socket descriptor */
	if((this->i_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Client-socket() error");
		exit(-1);
	}
	else
		printf("Client-socket() OK\n");
	
	memset(&server_address, 0x00, sizeof(struct sockaddr_in));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(this->i_port_no);
	 
	if((server_address.sin_addr.s_addr = inet_addr(this->str_server.c_str())) == (unsigned long)INADDR_NONE)
	{
	 
		/* When passing the host name of the server as a */
		/* parameter to this program, use the gethostbyname() */
		/* function to retrieve the address of the host server. */
		/***************************************************/
		/* get host address */
		hostp = gethostbyname(this->str_server.c_str());
		if(hostp == (struct hostent *)NULL)
		{
			printf("HOST NOT FOUND --> ");
			/* h_errno is usually defined */
			/* in netdb.h */
			printf("h_errno = %d\n",h_errno);
			printf("---This is a client program---\n");
		//	printf("Command usage: %s <server name or IP>\n", argv[0]);
			close(this->i_sd);
			exit(-1);
		}
		memcpy(&server_address.sin_addr, hostp->h_addr, sizeof(server_address.sin_addr));
	}
	 
	/* After the socket descriptor is received, the */
	/* connect() function is used to establish a */
	/* connection to the server. */
	/***********************************************/
	/* connect() to server. */
	if((i_status_value = connect(this->i_sd, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
	{
		perror("Client-connect() error");
		close(this->i_sd);
		exit(-1);
	}
	else
		printf("Connection established...\n");
		
		
	return i_status_value;
}


void IMTCPClient::Disconnect()
{
	close(this->i_sd);
}


int IMTCPClient::Read(char * p_c_buffer, int i_size)
{
	int i_status_value = -1;
	
	printf("Read function calling\n");
	
	i_status_value = read(this->i_sd, p_c_buffer, i_size);
	
	printf("Okundu...\n");
	
	if(i_status_value < 0)
	{
		perror("Client-read() error");
		close(this->i_sd);
		exit(-1);
	}
	else if (i_status_value == 0)
	{
		printf("Server program has issued a close()\n");
		close(this->i_sd);
		exit(-1);
	}
	
	return i_status_value;
}

int IMTCPClient::Write(char * p_c_data, int i_size)
{
	int i_status_value = -1;
	char c_temp;
	socklen_t length = sizeof(int);
	
	if(this->i_sd < 0)
	{
		perror("Connection is not established. \n");
		exit(-1);
	}
	
	printf("Sending some string to the f***ing %s...\n", this->str_server.c_str());
	
	i_status_value = write(this->i_sd, p_c_data, i_size);
	 
	if(i_status_value < 0)
	{
		perror("Client-write() error");
		i_status_value = getsockopt(this->i_sd, SOL_SOCKET, SO_ERROR, &c_temp, &length);
		
		if(i_status_value == 0)
		{
			/* Print out the asynchronously received error. */
			errno = c_temp;
			perror("SO_ERROR was");
		}
		
		close(this->i_sd);
		exit(-1);
	}
	else
	{
		printf("Client-write() is OK\n");
		printf("String successfully sent lol!\n");
	}
	
	return i_status_value;
	
}

