#ifndef ARCGPARSE_H
#define ARGPARSE_H

#include "arg.h"
#include "service.h"

#define ARGPARSE_PREFIX "DYN"
#define ARGPARSE_DELIM ":"

int   argparse_is_dynamic(const char*);
arg*  argparse_parse_arg(const char*);
char* argparse_get_thr(service_list*, const char*);

#endif
