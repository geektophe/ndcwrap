#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "conf.h"
#include "service.h"
#include "string_utils.h"

#define CONF_ROW_MAXLEN 81
#define CONF_DELIM ":"


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


service* conf_parse_row(const char* row) {

	if (! conf_check_row(row))
		return NULL;

	service* srv = service_new();

	if (NULL == srv) {
		PERROR();
	}

	string_words* parsed = string_split(row, CONF_DELIM);

	if (NULL == parsed) {
		PERROR();
	}

	service_set(srv, parsed->words[0], parsed->words[1], parsed->words[2]);
	string_words_free(parsed);
	return srv;
}


service_list* conf_parse_file(const char* path) {

	char row[CONF_ROW_MAXLEN];
	FILE* fp = fopen(path, "r");

	if (NULL == fp) {
		perror("could not open configutation file");
		return NULL;
	}

	service_list* config = service_list_new();

	if (NULL == config) {
		PERROR()
	}

	unsigned int lineno = 1;

	while(NULL != fgets(row, CONF_ROW_MAXLEN, fp)) {
		/* Strips trailing newline */
		int i=0;

		for (i=strlen(row)-1; i>=0; i--) {
			char pos = row[i];
			if ('\n' == row[i] || '\r' == row[i]) {
				 row[i] = '\0';
			} else {
				break;
			}
		}
		/* Parses row */
		service* srv = conf_parse_row(row);

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
