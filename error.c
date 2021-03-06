/***************************************************************
 *
 * error.c
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

