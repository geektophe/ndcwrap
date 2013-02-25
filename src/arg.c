#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arg.h"
#include "error.h"

arg* arg_new(void) {
	arg* new_arg = (arg*)malloc(sizeof(arg));

	if (NULL == new_arg) {
		PERROR();
	}
	new_arg->serv = NULL;
	new_arg->level = LEVEL_NULL;
	new_arg->deflt = NULL;
	return new_arg;
}


void arg_set(arg* target, const char* serv, criticity level,
              const char* deflt) {

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
	if (LEVEL_NULL != level) {
		target->level = level;
	}

	/* Sets serv deflt */
	if (NULL != deflt) {
		if (NULL != target->deflt) {
			free(target->deflt);
		}
		target->deflt = (char*)malloc(sizeof(char) * (strlen(deflt) + 1));

		if (NULL == target->deflt) {
			PERROR();
		}
		strncpy(target->deflt, deflt, strlen(deflt) + 1);
	}
}


void arg_free(arg* target) {
	if (NULL == target)
		return;

	/* Frees serv field */
	if (NULL != target->serv) {
		free(target->serv);
		target->serv = NULL;
	}

	/* Frees deflt field */
	if (NULL != target->deflt) {
		free(target->deflt);
		target->deflt = NULL;
	}

	/* Frees object memory */
	free(target);
}

