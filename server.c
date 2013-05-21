/***************************************************************
 *
 * server.c
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
#include <signal.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

// module headers
#include "network.h"
#include "database.h"
#include "server.h"
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
  printf ( "    -?\n"                      );
  printf ( "    --help\n"                  );
  printf ( "        Print this usage.\n"   );
  exit ( 0 );
  return 1;
}

// main loop
int main ( int argc, char *argv[] )
{
  server_param_t parameters =
  {
    NETWORK_DEFAULT_PORT
  };
  args_param_t args_param_list[] =
  {
    { "-p",     &parameters.port, argsInteger },
    { "--port", &parameters.port, argsInteger },
    { "-?",     NULL, usage                   },
    { "--help", NULL, usage                   },
    ARGS_DONE
  };
  int socketFile;
  int done;

  // process command line arguments
  argsProcess ( argc, argv, args_param_list );
  printf ( "Port: %d\n", parameters.port );

  // open / bind / listen on socket
  socketFile = initServer ( parameters.port );

  // let child processes die
  signal ( SIGCHLD, SIG_IGN );

  // endless loop
  done = 0;
  while ( !done )
  {
    // local variables
    int communicationSocketFile;
    int pid;

    // establish connection
    communicationSocketFile = getConnection ( socketFile );

    // fork
    pid = fork ( );

    // no child created
    if ( pid < 0 )
    {
      fatalError ( "Error on fork!", 1 );
    }

    // child
    else if ( 0 == pid )
    {
      close ( socketFile );
      service ( communicationSocketFile );
      exit ( 0 );
    }

    // else, parent
    close ( communicationSocketFile );
  } // endless loop

  // clean up
  close ( socketFile );
  return 0; 
}

// service loop
void service ( int pSocketFile )
{
  char buffer [ NETWORK_COMMUNICATION_BUFFER_SIZE ];
  int  done;

  // initialize database
  database_init ( );

  // endless loop
  done = 0;
  while ( !done )
  {
    // receive message
    receiveMessage ( pSocketFile, buffer, sizeof ( buffer ) );
    printf ( "Here is the message: %s\n", buffer );

    // send reply
    if ( 0 == strncmp ( NETWORK_QUIT_MESSAGE, buffer, strlen ( NETWORK_QUIT_MESSAGE ) ) )
    {
      // all done
      sendMessage ( pSocketFile, NETWORK_QUIT_MESSAGE );
      done = 1;
    }
    else
    {
      database_addMessage ( "user_unknown", buffer );
      sendMessage ( pSocketFile, "I got your message" );
    }
  }

  // clean up
  database_close ( );
}

