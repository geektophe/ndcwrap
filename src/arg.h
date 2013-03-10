#ifndef ARG_H
#define ARG_H

/* Nagios criticity levels definition. */
typedef enum criticity {
	LEVEL_NULL,
	LEVEL_WARN,
	LEVEL_CRIT
} criticity_t;

/* Dynamic command line argument defitition */
typedef struct arg {
	char*       serv;   /* Service name */
	criticity_t level;  /* Service warn bound */
	char*       deflt;  /* Service warn bound */
} arg_t;

/* Returns a pointer to a new arg_t structure. */
arg_t* arg_new(void);

/* Sets an arg_t structure attributes. */
void   arg_set(arg_t*, const char*, criticity_t, const char*);

/* Frees an arg_t pointer structure. */
void   arg_free(arg_t*);

#endif
