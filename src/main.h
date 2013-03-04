#ifndef CLIW_H
#define CLIW_H

#define DCLIWRAP_CONFIG "/etc/dcliwrap.conf"
#define DCLIWRAP_ENVVAR "DCLIWRAP_CONFIG"
#define ECRITICAL 3

int main(int, char**);
void error(char*, int);

#endif
