/***************************************************************
 *
 * client.c
 * ...
 *
 ***************************************************************
 *
 * This software was written in 2013 by the following author(s):
 * Brendan A R Sechter <bsechter@sennue.com>
 *
 * To the extent possible under law, the author(s) have
 * dedicated all copyright and related and neighboring rights
 * to this software to the public domain worldwide. This
 * software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain
 * Dedication along with this software. If not, see
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
 *
 * Please release derivative works under the terms of the CC0
 * Public Domain Dedication.
 *
 ***************************************************************/

// library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

// module headers
#include "network.h"
#include "client.h"
#include "args.h"
#include "error.h"

// function prototypes
void service ( int pSocketFile );

// program usage
int usage ( int argc, char *argv[], int argn, args_param_t *args_param, void *data )
{
  printf ( "Usage: %s [params]\n", argv[0] );
  printf ( "    -p     <port number>\n"    );
  printf ( "    --port <port number>\n"    );
  printf ( "        Set port number.\n"    );
  printf ( "    -h     <port number>\n"    );
  printf ( "    --host <port number>\n"    );
  printf ( "        Set host.\n"           );
  printf ( "    -?\n"                      );
  printf ( "    --help\n"                  );
  printf ( "        Print this usage.\n"   );
  exit ( 0 );
  return 1;
}

// client main program
int main ( int argc, char *argv[] )
{
  client_param_t parameters =
  {
    NETWORK_DEFAULT_PORT,
    NETWORK_DEFAULT_HOST
  };
  args_param_t args_param_list[] =
  {
    { "-p",     &parameters.port, argsInteger },
    { "--port", &parameters.port, argsInteger },
    { "-h",     &parameters.host, argsString  },
    { "--host", &parameters.host, argsString  },
    { "-?",     NULL,             usage       },
    { "--help", NULL,             usage       },
    ARGS_DONE
  };
  int socketFile;

  // process command line arguments
  argsProcess ( argc, argv, args_param_list );
  printf ( "Port: %d\n", parameters.port );
  printf ( "Host: %s\n", parameters.host );

  // open socket
  socketFile = initClient ( parameters.port, parameters.host );

  // run service loop
  service ( socketFile );

  // clean up
  close ( socketFile );
  return 0;
}

// service loop
void service ( int pSocketFile )
{
  char buffer [ NETWORK_COMMUNICATION_BUFFER_SIZE ];
  int  done;

  // endless loop
  done = 0;
  while ( !done )
  {
    // get message
    printf ( "Please enter the message: " );
    bzero ( buffer, sizeof ( buffer ) );
    fgets ( buffer, sizeof ( buffer ) - 1, stdin );

    // remove newline
    buffer [ strlen ( buffer ) - 1 ] = '\0';

    // send message
    sendMessage ( pSocketFile, buffer );

    // receive message
    receiveMessage ( pSocketFile, buffer, sizeof ( buffer ) );
    printf ( "%s\n", buffer );

    // check for quit message
    if ( 0 == strncmp ( NETWORK_QUIT_MESSAGE, buffer, strlen ( NETWORK_QUIT_MESSAGE ) ) )
    {
      // all done
      done = 1;
    }
  }
}

