#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "error.h"
#include "conf.h"
#include "service.h"
#include "string_utils.h"

#define CONF_ROW_MAXLEN 81
#define CONF_DELIM ":"


/**
 * Returns a configuration file path. The default path ginev in fist parameter
 * may be overriden if sipecified in the environmanet variable wihch name is
 * given in second parameter.
 *
 * If path given in any of default path or in the environment variable does not
 * exist, the returned value is NULL.
 *
 * Caution, returned string has to be freed using free function.
 *
 * @param[in] deflt_path	The default configuration file ptah.
 * @param[in] env_name		Name of environment varible which may
 * 				override default path.
 * @return char*
 */
char* conf_get_path(char* deflt_path, char* env_name) {
	char* path = NULL;

	if (NULL != env_name) {
		path = getenv(env_name);
	} else {
		path = deflt_path;
	}
	if (NULL == path) {
		return NULL;
	}
	if (0 == access(path, R_OK)) {
		return path;
	} else {
		return NULL;
	}
}


/**
 * Checks if a configuration file row format is valid.
 *
 * Rows should match the format above.
 *
 *	NAME:WARN VAL:CRIT VAL
 *
 * @param[in] row	The command row to check.
 * @return int
 */
int conf_check_row(const char* row) {
	// Row format should be NAME:WARN:CRIT
	// Counts the number of words using ":" as separator
	int words = 0;
	int new_word = 0;

	if (NULL == row || 0 == strlen(row) || CONF_DELIM[0] == row[0] ||
	    CONF_DELIM[0] == row[ strlen(row) - 1 ])
		return 0;

	unsigned int i;

	for (i=0; i<strlen(row); i++) {
		if (row[i] != CONF_DELIM[0] && new_word == 0) {
			words++;
			new_word = 1;
		} else if (row[i] == CONF_DELIM[0]) {
			new_word = 0;
		}
	}
	return words == 3;
}


/**
 * Parses a config file row into a service_t structure and returns a pointer to
 * the initialized structure.
 *
 * Rows should match the format above.
 *
 *	NAME:WARN VAL:CRIT VAL
 *
 * Caution, returned pointer has to be freed using service_free function.
 *
 * @param[in] row	The command row to parse.
 * @return service_t*
 */
service_t* conf_parse_row(const char* row) {

	if (! conf_check_row(row))
		return NULL;

	service_t* srv = service_new();

	if (NULL == srv) {
		PERROR();
	}

	string_words_t* parsed = string_split(row, CONF_DELIM);

	if (NULL == parsed) {
		PERROR();
	}

	service_set(srv, parsed->words[0], parsed->words[1], parsed->words[2]);
	string_words_free(parsed);
	return srv;
}


/**
 * Parses a whole config file into a service_list_t structure and returns a
 * pointer to the structrue filled with service_t structures.
 *
 * Caution, returned pointer has to be freed using service_list_free function.
 *
 * @param[in] path		The configuration file to parse.
 * @return service_list_t*
 */
service_list_t* conf_parse_file(const char* path) {

	char row[CONF_ROW_MAXLEN];
	FILE* fp = fopen(path, "r");

	if (NULL == fp) {
		perror("could not open configutation file");
		return NULL;
	}

	service_list_t* config = service_list_new();

	if (NULL == config) {
		PERROR()
	}

	unsigned int lineno = 1;

	while(NULL != fgets(row, CONF_ROW_MAXLEN, fp)) {
		/* Strips trailing newline */
		int i=0;

		for (i=strlen(row)-1; i>=0; i--) {
			if ('\n' == row[i] || '\r' == row[i]) {
				 row[i] = '\0';
			} else {
				break;
			}
		}
		/* Parses row */
		service_t* srv = conf_parse_row(row);

		if (NULL == srv) {
			fprintf(stderr, "igrored invalid row on line %d\n",
			        lineno);
			continue;
		}
		service_list_append(config, srv);
		lineno++;

	}
	fclose(fp);
	return config;
}
