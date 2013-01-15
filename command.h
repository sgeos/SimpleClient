#ifndef COMMAND_H
#define COMMAND_H

#include <stddef.h>

// types
typedef struct command_param_t command_param_t;
typedef int ( * command_func_t ) ( const char *pBuffer, command_param_t *pCommandParameter, void *pData );
struct command_param_t
{
  const char     * command;
  command_func_t   callback;
  void           * data;
};

// constants
#define COMMAND_FINAL_COMMAND  NULL
#define COMMAND_FINAL_CALLBACK NULL

// final argument in list
#define COMMAND_DONE { COMMAND_FINAL_COMMAND, COMMAND_FINAL_CALLBACK }

// process command line arguments
//void argsProcess (int argc, char *argv[], args_param_t *pParams);

// scan basic types of command line arguments
//int  argsInteger  ( int argc, char *argv[], int argn, struct args_param_t *args_param, void *data );
//int  argsFloat    ( int argc, char *argv[], int argn, struct args_param_t *args_param, void *data );
//int  argsString   ( int argc, char *argv[], int argn, struct args_param_t *args_param, void *data );
//char argsGetToken ( void );
//void argsSetToken ( char pToken );

#endif // COMMAND_H

