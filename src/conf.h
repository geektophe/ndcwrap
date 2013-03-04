#ifndef CONF_H
#define CONF_H

#include "service.h"

char*           conf_get_path(char*, char*);
int             conf_check_row(const char*);
service_t*      conf_parse_row(const char*);
service_list_t* conf_parse_file(const char*);

#endif
