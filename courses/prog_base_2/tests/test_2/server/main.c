/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "server.h"

int main()
{
    lib_init();
    socket_t * server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);
    char buf[10000];
    socket_t * client = NULL;
     while(1)
    {
        client = socket_accept(server);
        socket_read(client, buf, sizeof(buf));
        printf("%s",buf);
        if (strlen(buf) != 0){
        http_request_t rs;
        rs = http_request_parse(buf);
        if (strcmp(rs.method,"GET") == 0 && strcmp(rs.uri, "/info") == 0 )
        {
            server_info(client);
        }

        }
    }
    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "server.h"
#include <winsock2.h>
#include <windows.h>
#include "cJSON.h"
#include <time.h>


#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen

typedef struct {
    char * author;
    char * book;
    char * time;
}author_t;

int main(void) {

    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char buffer[MAXBUFLEN];
    memset(buffer,0,MAXBUFLEN);
    // Initialize Windows Socket DLL
    status = WSAStartup(MAKEWORD(2, 2), &Data);
    if(status != 0)
    {
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }
	// Get IP address from host name
	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // zero the sockaddr_in structure
    recvSockAddr.sin_port=htons(PORT); // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET; // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip); // specify ip address
	// Create socket
	recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(recvSocket == INVALID_SOCKET)
	{
		printf("ERROR: socket unsuccessful\r\n");
             WSACleanup();
		system("pause");
		return 0;
	}
    // Connect
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        return 0;
    }
    // Send request
    char request[200];
    sprintf(request, "GET /test/var/11?format=json HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);

	// Receieve
    numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
	// Print out receieved socket data
    printf("%s\r\n", buffer);

    char * json=strstr(buffer,"{");


    cJSON * SI = cJSON_CreateObject();

    SI=cJSON_Parse(json);


    author_t * author=malloc(sizeof(author_t));

    author->author=malloc(strlen(cJSON_GetObjectItem(SI,"author")->valuestring)+1);
    strcpy(author->author,cJSON_GetObjectItem(SI,"author")->valuestring);

    author->book=malloc(strlen(cJSON_GetObjectItem(SI,"book")->valuestring)+1);
    strcpy(author->book,cJSON_GetObjectItem(SI,"book")->valuestring);

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    author->time=malloc(strlen(asctime(timeinfo)));
    strcpy(author->time,asctime(timeinfo));
    author->time[strlen(author->time)-1]='\0';

    cJSON * SM = cJSON_CreateObject();
    cJSON_AddItemToObject(SM, "author", cJSON_CreateString(author->author));
    cJSON_AddItemToObject(SM, "book", cJSON_CreateString(author->book));
    cJSON_AddItemToObject(SM, "time", cJSON_CreateString(author->time));
    char * jsonSM = cJSON_Print(SM);



    system("pause");



        lib_init();
    socket_t * server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);
    char buf[10000];
    socket_t * client = NULL;
     while(1)
    {
        client = socket_accept(server);
        socket_read(client, buf, sizeof(buf));
        printf("%s",buf);
        if (strlen(buf) != 0){
        http_request_t rs;
        rs = http_request_parse(buf);
        if (strcmp(rs.method,"GET") == 0 && strcmp(rs.uri, "/info") == 0 )
        {
            server_info(client);

        }
         if (strcmp(rs.method,"GET") == 0 && strcmp(rs.uri, "/external") == 0 )
        {
            server_sent(client,jsonSM);
        }

        }
    }
      system("pause");
    return 0;
}



