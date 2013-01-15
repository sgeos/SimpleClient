#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>

#define NETWORK_QUIT_MESSAGE              "exit"
#define NETWORK_DEFAULT_HOST              "localhost"
#define NETWORK_DEFAULT_PORT              51717
#define NETWORK_BACKLOG_QUEUE             5
#define NETWORK_COMMUNICATION_BUFFER_SIZE 256

int  openSocket     ( void );
void bindSocket     ( int pSocketFile, int pPort );
int  initServer     ( int pPort );
int  initClient     ( int pPort, const char *pHost );
int  getConnection  ( int pSocketFile );
void sendMessage    ( int pSocketFile, const char *pMessage );
void receiveMessage ( int pSocketFile, char *pBuffer, int pSize );

#endif // NETWORK_H

