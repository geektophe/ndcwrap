#ifndef CLIW_H
#define CLIW_H

#define DCLIWRAP_CONFIG "/etc/dcliwrap.conf"
#define DCLIWRAP_CONFIG_ENVVAR "DCLIWRAP_CONFIG"
#define DCLIWRAP_DEBUG_ENVVAR "DCLIWRAP_DEBUG"
#define ECRITICAL 3

/* Main function */
int main(int, char**);

/* Displayes an error message and exits. */
void error(char*, int);

/* Tests if the debug environmont variable is set. */
int is_debug(void);

#endif
