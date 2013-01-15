// library headers
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// module headers
#include "command.h"

int commandScan ( const char *pBuffer, char *pFormat, ... )
{
  // local variables
  int     result;
  va_list arguments;

  va_start ( arguments, pFormat );
  result = vsscanf ( pBuffer, pFormat, arguments );
  va_end ( arguments );
  return result;
}

const char * commandMatch ( const char *pBuffer, const char *pCommand )
{
  int size = strlen ( pCommand );

  // if this is the correct command
  if ( 0 == strncmp ( pCommand, pBuffer, size ) )
  {
    // return the data after the command
    return &pBuffer [ size ];
  }
  // else
  return NULL;
}

int commandEntryProcess ( const char * pBuffer, command_param_t * pCommandParameter )
{
  if ( commandMatch ( pBuffer, pCommandParameter->command ) )
  {
    return pCommandParameter->callback ( pBuffer, pCommandParameter, pCommandParameter->data );
  }
  // else
  return 0;
}

int commandProcess ( const char * pBuffer, command_param_t * pCommandList )
{
  // local variables
  int result = 0;
  int i;

  for ( i = 0; COMMAND_FINAL_COMMAND != pCommandList [ i ] .command; i++ )
  {
    result = commandEntryProcess ( pBuffer, &pCommandList [ i ] );
    if ( result )
    {
      break;
    }
  }

  return result;
}

// example program
#ifdef COMMAND_MAIN

int commandScanDie ( const char *pBuffer, command_param_t *pCommandParameter, void *pData )
{
  void       ** dataParameter = ( void ** ) pData;
  char        * message       = dataParameter [ 0 ];
  int         * number        = dataParameter [ 1 ];
  const char  * scanBuffer    = commandMatch ( pBuffer, pCommandParameter->command );
  int           result        = commandScan ( scanBuffer, "%d/%s", number, message );

  printf ( "DIE\n" );
  printf ( "Message:   %s\n",  message );
  printf ( "Exit Code: %d\n", *number );
  if ( 0 == result )
  {
    result = -1;
  }
  exit ( *number );
  return result;
}

int commandScanMessage ( const char *pBuffer, command_param_t *pCommandParameter, void *pData )
{
  const char  * message = commandMatch ( pBuffer, pCommandParameter->command );

  printf ( "MESSAGE\n" );
  printf ( "Message:   %s\n", message );
  return 1;
}

int main ( void )
{
  char         buffer  [ 256 ] = "";
  char         message [ 256 ] = "";
  int          number          = 0;
  void       * dataDie [ ]     = { message, &number };
  command_param_t commandList [ ] =
  {
    { "$die://",     commandScanDie,     (void *)dataDie },
    { "$message://", commandScanMessage, NULL            },
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

#endif // COMMAND_MAIN

