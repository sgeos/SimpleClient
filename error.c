#include <stdlib.h>
#include <stdio.h>

void fatalError ( const char *pMessage, int pExitCode )
{
  fprintf ( stderr, "FATAL ERROR : %s\n", pMessage );
  fflush  ( stderr ); 
  exit    ( pExitCode );
}

void error      ( const char *pMessage )
{
  fprintf ( stderr, "ERROR : %s\n", pMessage );
  fflush  ( stderr ); 
}

void warning    ( const char *pMessage )
{
  fprintf ( stderr, "WARNING : %s\n", pMessage );
  fflush  ( stderr ); 
}

