#ifndef ERROR_H
#define ERROR_H

void fatalError ( const char *pMessage, int pExitCode );
void error      ( const char *pMessage );
void warning    ( const char *pMessage );

#endif // ERROR_H

