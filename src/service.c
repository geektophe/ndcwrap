#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "service.h"
#include "error.h"


/* @funcstatic tcode_readdata *************************************************
 *
 * Read Etcode.dat data file
 *
 * @param [w] table1 [AjPFTestcode*] data object
 * @param [r] datafile [AjPFile] data file object
 * @return [AjBool] true if successful read
 * @@
 *****************************************************************************/
service_t* service_new(void) {
	service_t* new_service = (service_t*)malloc(sizeof(service_t));

	if (NULL == new_service) {
		PERROR();
	}
	new_service->serv = NULL;
	new_service->warn = NULL;
	new_service->crit = NULL;
	new_service->next = NULL;
	return new_service;
}


void service_set(service_t* target, const char* serv, const char* warn,
                 const char* crit) {

	if (NULL == target) {
		ERROR("target is not initialized.", 1);
	}

	/* Sets serv field */
	if (NULL != serv) {
		if (NULL != target->serv) {
			free(target->serv);
		}
		target->serv = (char*)malloc(sizeof(char) * (strlen(serv) + 1));

		if (NULL == target->serv) {
			PERROR();
		}
		strncpy(target->serv, serv, strlen(serv) + 1);
	}

	/* Sets serv warn */
	if (NULL != warn) {
		if (NULL != target->warn) {
			free(target->warn);
		}
		target->warn = (char*)malloc(sizeof(char) * (strlen(warn) + 1));

		if (NULL == target->warn) {
			PERROR();
		}
		strncpy(target->warn, warn, strlen(warn) + 1);
	}

	/* Sets serv crit */
	if (NULL != crit) {
		if (NULL != target->crit) {
			free(target->crit);
		}
		target->crit = (char*)malloc(sizeof(char) * (strlen(crit) + 1));

		if (NULL == target->crit) {
			PERROR();
		}
		strncpy(target->crit, crit, strlen(crit) + 1);
	}
}


void service_free(service_t* target) {
	if (NULL == target)
		return;

	target->next = NULL;

	/* Frees serv field */
	if (NULL != target->serv) {
		free(target->serv);
		target->serv = NULL;
	}

	/* Frees warn field */
	if (NULL != target->warn) {
		free(target->warn);
		target->warn = NULL;
	}

	/* Frees crit field */
	if (NULL != target->crit) {
		free(target->crit);
		target->crit = NULL;
	}

	/* Frees object memory */
	free(target);
}


service_list_t* service_list_new(void) {
	service_list_t* new_list = (service_list_t*)malloc(sizeof(service_list_t));

	if (NULL == new_list) {
		PERROR();
	}
	new_list->count = 0;
	new_list->first = NULL;
	new_list->last = NULL;
	return new_list;
}


void service_list_free(service_list_t* target) {

	/* Recursively frees existing list members */
	if (NULL != target->first) {
		service_t* current = target->first;

		while (NULL != current) {
			service_t* next = current->next;
			service_free(current);
			current = next;
		}
	}

	/* Freed target itself */
	target->first = NULL;
	target->last = NULL;
	target->count = 0;
	free(target);
}


void service_list_append(service_list_t* target, service_t* child) {
	if (NULL == target->first) {
		target->first = child;
		target->last = child;
	} else {
		target->last->next = child;
		target->last = child;
	}
	target->count++;
}


service_t* service_list_lookup(service_list_t* source, const char* serv) {
	service_t* current = source->first;

	while (NULL != current) {
		char *cur_serv = current->serv;

		if (NULL != cur_serv && 0 == strcmp(cur_serv, serv)) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}
