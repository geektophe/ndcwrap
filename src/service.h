#ifndef SERVICE_H
#define SERVICE_H

struct service {
	char *serv;           /* Service name */
	char *warn;           /* Service warn bound */
	char *crit;           /* Service crit bound */
	struct service *next; /* Next element in the list */
};
typedef struct service service;

struct service_list {
	unsigned int count;
	service *first;
	service *last;

};

typedef struct service_list service_list;

/* Service related functions */
service* service_new(void);
void service_set(service*, const char*, const char*, const char*);
void service_free(service*);

/* Service list related functions */
service_list* service_list_new(void);
void service_list_set(service_list*);
void service_list_append(service_list*, service*);
void service_list_free(service_list*);
service* service_list_lookup(service_list*, const char*);

#endif
