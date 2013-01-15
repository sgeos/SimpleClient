#ifndef ARGS_H
#define ARGS_H

#include <stddef.h>

// types
typedef struct args_param_t args_param_t;
typedef int (*args_func_t)(int argc, char *argv[], int argn, args_param_t *args_param, void *data);
struct args_param_t
{
  const char  *flag;
  void        *data;
  args_func_t func;
};

// constants
#define ARGS_DEFAULT_TOKEN '-'
#define ARGS_FINAL_FLAG    NULL
#define ARGS_FINAL_DATA    NULL
#define ARGS_FINAL_FUNC    NULL

// final argument in list
#define ARGS_DONE       { ARGS_FINAL_FLAG, ARGS_FINAL_DATA, ARGS_FINAL_FUNC }

// process command line arguments
void argsProcess (int argc, char *argv[], args_param_t *pParams);

// scan basic types of command line arguments
int  argsInteger  ( int argc, char *argv[], int argn, struct args_param_t *args_param, void *data );
int  argsFloat    ( int argc, char *argv[], int argn, struct args_param_t *args_param, void *data );
int  argsString   ( int argc, char *argv[], int argn, struct args_param_t *args_param, void *data );
char argsGetToken ( void );
void argsSetToken ( char pToken );

#endif // ARGS_H

