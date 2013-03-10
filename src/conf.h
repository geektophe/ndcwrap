#ifndef CONF_H
#define CONF_H

#include "service.h"

/* Returns a configuration file path. The default path ginev in fist parameter
 * may be overriden if sipecified in the environmanet variable wihch name is
 * given in second parameter. */
char*           conf_get_path(char*, char*);

/* Checks if a configuration file row format is valid. */
int             conf_check_row(const char*);

/* Parses a config file row into a service_t structure. */
service_t*      conf_parse_row(const char*);

/* Parses a whole config file into a service_list_t structure. */
service_list_t* conf_parse_file(const char*);

#endif
