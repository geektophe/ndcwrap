#ifndef ARCGPARSE_H
#define ARGPARSE_H

#include "arg.h"
#include "service.h"

#define ARGPARSE_PREFIX "DYN"
#define ARGPARSE_DELIM ":"

/* Checks if a command line parameter is a parsable dynamic argument. */
int    argparse_is_dynamic(const char*);

/* Parses a dynamic command line parameter, and return an arg_t pointer to the
 * corresponding arg_t sructure. */
arg_t* argparse_parse_arg(const char*);

/* Parses a dynamic command line parameter, and tries to find out corresponding
 * threshold in a set of services definition. */
char*  argparse_get_thr(service_list_t*, const char*);

#endif
