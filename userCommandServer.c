// library headers
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// module headers
#include "command.h"
#include "userCommand.h"
#include "network.h"

int userCommandServerReceiveDie ( const char *pBuffer, command_param_t *pCommandParameter, void *pData )
{
  char          message [ 256 ] = "";
  int           number          = 0;
  const char  * scanBuffer    = commandMatch ( pBuffer, pCommandParameter->command );
  int           result        = commandScan  ( scanBuffer, "%d/%s", &number, message );

  printf ( "Message:   %s\n",  message );
  printf ( "Exit Code: %d\n", *number );
  if ( 0 == result )
  {
    result = -1;
  }
  exit ( *number );
  return result;
}

int userCommandServerReceiveMessage ( const char *pBuffer, command_param_t *pCommandParameter, void *pData )
{
  const char  * message = commandMatch ( pBuffer, pCommandParameter->command );

  printf ( "Message:   %s\n", message );
  return 1;
}

int userCommandServerReceive ( char * pBuffer, int pSize )
{
  void       * dataDie [ ]     = { message, &number };
  command_param_t commandList [ ] =
  {
    { USER_COMMAND_MESSAGE, userCommandServerMessage, NULL            },
    { USER_COMMAND_DIE,     userCommandServerDie,     (void *)dataDie },
    COMMAND_DONE
  };

  while ( 1 )
  {
    printf ( "> " );
    fflush ( stdout );
    fgets ( buffer, sizeof ( buffer ), stdin );
    buffer [ strlen ( buffer ) - 1 ] = '\0';
    commandProcess ( buffer, commandList );
  }
  return 0;
}

int userCommandServerSendMessage ( int pSocketFile, char * pBuffer, int pSize, const char *pUser, const char *pMessage )
{
  snprintf ( pBuffer, pSize, "%s%s/%s", USER_COMMAND_MESSAGE, pUser, pMessage );
  sendMessage ( pSocketFile, pBuffer );
  return 0;
}

int userCommandServerSendUser ( int pSocketFile, char * pBuffer, int pSize, const char *pUser )
{
  snprintf ( pBuffer, pSize, "%s%s", USER_COMMAND_USER, pUser );
  sendMessage ( pSocketFile, pBuffer );
  return 0;
}

int userCommandServerSendExit ( int pSocketFile, char * pBuffer, int pSize, int pExitCode, const char *pMessage )
{
  snprintf ( pBuffer, pSize, "%s%d/%s", USER_COMMAND_EXIT, pExitCode, pMessage );
  sendMessage ( pSocketFile, pBuffer );
  return 0;
}

int userCommandServerSendDie ( int pSocketFile, char * pBuffer, int pSize, int pExitCode, const char *pMessage )
{
  snprintf ( pBuffer, pSize, "%s%d/%s", USER_COMMAND_DIE, pExitCode, pMessage );
  sendMessage ( pSocketFile, pBuffer );
  return 0;
}

