#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arg.h"
#include "error.h"


/**
 * Returns a pointer to a new arg_t structure.
 *
 * Caution, returned poirnter has to be freed using arg_free function.
 *
 * @return arg_t*
 */
arg_t* arg_new(void) {
	arg_t* new_arg = (arg_t*)malloc(sizeof(arg_t));

	if (NULL == new_arg) {
		PERROR();
	}
	new_arg->serv = NULL;
	new_arg->level = LEVEL_NULL;
	new_arg->deflt = NULL;
	return new_arg;
}


/**
 * Sets an arg_t structure attributes.
 *
 * Argument positions which passed value is NULL are ignored.
 *
 * @param[in] target	The target arg_t pointer to set attributes value
 * @param[in] serv		The service name to set as serv attrubute
 * @param[in] level		The criticity level to as level attrubute
 * @param[in] deflt		The value to set as deflt attrubute
 * @return void
 */
void arg_set(arg_t* target, const char* serv, criticity_t level,
              const char* deflt) {

	if (NULL == target) {
		ERROR("target is not initialized.", 1);
	}

	/* Sets serv field */
	if (NULL != serv) {
		if (NULL != target->serv) {
			free(target->serv);
		}
		target->serv = strdup(serv);

		if (NULL == target->serv) {
			PERROR();
		}
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
		target->deflt = strdup(deflt);

		if (NULL == target->deflt) {
			PERROR();
		}
	}
}


/**
 * Frees an ang_t pointer structure.
 *
 * @param[in] target	The arg_t structure pointer to free.
 * @return void
 */
void arg_free(arg_t* target) {
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

