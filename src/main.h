#ifndef CLIW_H
#define CLIW_H

#define DCLIWRAP_CONFIG "/etc/dcliwrap.conf"
#define DCLIWRAP_CONFIG_ENVVAR "DCLIWRAP_CONFIG"
#define DCLIWRAP_DEBUG_ENVVAR "DCLIWRAP_DEBUG"
#define ECRITICAL 3

int main(int, char**);
void error(char*, int);
int is_debug(void);

#endif
