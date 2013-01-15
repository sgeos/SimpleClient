// library headers
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <netdb.h>

// module headers
#include "network.h"
#include "error.h"

int openSocket ( void )
{
  int result;

  result = socket ( AF_INET, SOCK_STREAM, 0 );
  if ( result < 0 )
  {
    fatalError ( "Error opening socket!", 1 );
  }
  return result;
}

void bindSocket ( int pSocketFile, int pPort )
{
  // local variables
  struct sockaddr_in address;
  int                size;

  // zero data
  size = sizeof ( address );
  bzero ( (char *)&address, size );

  // initialize data
  address.sin_family      = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port        = htons ( pPort );

  // bind
  if ( bind ( pSocketFile, (struct sockaddr *)&address, size ) < 0 )
  {
    fatalError ( "Error on binding!", 1 );
  }
}

void connectSocket ( int pSocketFile, int pPort, const char *pHost )
{
  // local variables
  struct sockaddr_in   address;
  struct hostent     * server;
  int size;

  // get server info
  server = gethostbyname ( pHost );
  if ( server == NULL ) {
    fatalError ( "No such host!\n", 0 );
  }

  // zero data
  size = sizeof ( address );
  bzero ( (char *)&address, size );

  // initialize data
  address.sin_family = AF_INET;
  address.sin_port   = htons ( pPort );
  bcopy ( (char *)server->h_addr, (char *)&address.sin_addr.s_addr, server->h_length );

  // connect
  if ( connect ( pSocketFile, (struct sockaddr *)&address, size ) < 0 )
  {
    fatalError ( "Error connecting!", 1 );
  }
}

int initServer ( int pPort )
{
  // local variables
  int socketFile;

  // open / bind / listen on socket
  socketFile = openSocket ( );
  bindSocket ( socketFile, pPort );
  listen ( socketFile, NETWORK_BACKLOG_QUEUE );

  return socketFile;
}

int initClient ( int pPort, const char *pHost )
{
  // local variables
  int socketFile;

  // open socket and connect to host
  socketFile = openSocket ( );
  connectSocket ( socketFile, pPort, pHost );

  return socketFile;
}

int getConnection ( int pSocketFile )
{
  struct sockaddr_in address;
  socklen_t          size;
  int                socketFile;

  size = sizeof ( address );
  socketFile = accept ( pSocketFile, (struct sockaddr *)&address, &size );
  if ( socketFile < 0 )
  {
    fatalError ( "Error on accept!", 1 );
  }
  return socketFile;
}

void sendMessage ( int pSocketFile, const char *pMessage )
{
  int result;
  int size = strlen ( pMessage );
  result = write ( pSocketFile, pMessage, size );
  if ( result < 0 )
  {
    fatalError ( "Error writing to socket!", 1 );
  }
}

void receiveMessage ( int pSocketFile, char *pBuffer, int pSize )
{
  int result;
  bzero ( pBuffer, pSize );
  result = read ( pSocketFile, pBuffer, pSize - 1 );
  if ( result < 0 )
  {
    fatalError ( "Error reading from socket!", 1 );
  }
}

