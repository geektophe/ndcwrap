#ifndef CONF_H
#define CONF_H

#include "service.h"

int conf_check_row(const char*);
service* conf_parse_row(const char*);
service_list *conf_parse_file(const char*);

#endif
