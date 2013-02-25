#ifndef ARG_H
#define ARG_H

typedef enum criticity {
	LEVEL_NULL,
	LEVEL_WARN,
	LEVEL_CRIT
} criticity;

typedef struct arg {
	char*     serv;           /* Service name */
	criticity level;           /* Service warn bound */
	char*     deflt;           /* Service warn bound */
} arg;


arg* arg_new(void);
void arg_set(arg*, const char*, criticity, const char*);
void arg_free(arg*);

#endif
