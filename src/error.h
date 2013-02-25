#ifndef ERROR_H
#define ERROR_H

#include <errno.h>
#include <stdio.h>
#include <string.h>

/* PERROR macro to report errors */
#define PERROR() \
fprintf(stderr, "error: %s:%d (%s): %s", __FILE__, __LINE__, __FUNCTION__, \
        strerror(errno)); \
exit(errno);

/* ERROR macro to report errors */
#define ERROR(mesg, code) \
fprintf(stderr, "error: %s:%d (%s): %s", __FILE__, __LINE__, __FUNCTION__, \
        mesg); \
exit(code);

#endif
