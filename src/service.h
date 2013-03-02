#ifndef SERVICE_H
#define SERVICE_H

struct service {
	char *serv;           /* Service name */
	char *warn;           /* Service warn bound */
	char *crit;           /* Service crit bound */
	struct service *next; /* Next element in the list */
};
typedef struct service service_t;

struct service_list {
	unsigned int count;
	service_t *first;
	service_t *last;
};
typedef struct service_list service_list_t;

/* Service related functions */
service_t* service_new(void);
void       service_set(service_t*, const char*, const char*, const char*);
void       service_free(service_t*);

/* Service list related functions */
service_list_t* service_list_new(void);
void            service_list_set(service_list_t*);
void            service_list_append(service_list_t*, service_t*);
void            service_list_free(service_list_t*);
service_t*      service_list_lookup(service_list_t*, const char*);

#endif
