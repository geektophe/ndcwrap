#ifndef ARG_H
#define ARG_H

typedef enum criticity {
	LEVEL_NULL,
	LEVEL_WARN,
	LEVEL_CRIT
} criticity_t;

typedef struct arg {
	char*       serv;           /* Service name */
	criticity_t level;           /* Service warn bound */
	char*       deflt;           /* Service warn bound */
} arg_t;


arg_t* arg_new(void);
void   arg_set(arg_t*, const char*, criticity_t, const char*);
void   arg_free(arg_t*);

#endif
