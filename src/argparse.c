#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "argparse.h"
#include "arg.h"
#include "error.h"
#include "service.h"
#include "string_utils.h"


int argparse_is_dynamic(const char* strarg) {
	size_t sz = strlen(ARGPARSE_PREFIX) + strlen(ARGPARSE_DELIM);
	int res = 0;

	char *prefix = (char*)malloc(sizeof(char) * (sz + 1));

	if (NULL == prefix) {
		PERROR();
	}

	snprintf(prefix, sz+1, "%s%s", ARGPARSE_PREFIX, ARGPARSE_DELIM);
	res = strncmp(prefix, strarg, sz);
	free(prefix);
	return res == 0;
}


arg_t* argparse_parse_arg(const char* strarg) {
	// Row format should be DYN:NAME:WARN:DEFAULT
	// Counts the number of words using ":" as separator
	string_words_t* parsed = string_split(strarg, ARGPARSE_DELIM);

	if (NULL == parsed) {
		PERROR();
	}

	char **words = parsed->words;
	arg_t* parsed_arg = NULL;

	if ( 4 == parsed->count &&
	    (0 == strncmp(words[2],"WARN",4) || 0 == strncmp(words[2],"CRIT",4))
	    ) {
		parsed_arg = arg_new();
		criticity_t level = LEVEL_NULL;

		if (0 == strncmp(words[2],"WARN",4)) {
			level = LEVEL_WARN;
		} else {
			level = LEVEL_CRIT;
		}
		arg_set(parsed_arg, words[1], level, words[3]);
	}

	string_words_free(parsed);
	return parsed_arg;
}


char* argparse_get_thr(service_list_t* services, const char* strarg) {
	char * res = NULL;

	if (!argparse_is_dynamic(strarg)) {
		res = strdup(strarg);

		if (NULL == res) {
			return NULL;
		}
		return res;
	}

	arg_t* parsed = argparse_parse_arg(strarg);

	if (NULL == parsed) {
		return NULL;
	}

	service_t* srv = service_list_lookup(services, parsed->serv);

	if (NULL == srv) {
		res = strdup(parsed->deflt);
	} else {
		if (LEVEL_WARN == parsed->level) {
			res = strdup(srv->warn);
		} else {
			res = strdup(srv->crit);
		}
	}
	if (NULL == res) {
		PERROR();
	}
	arg_free(parsed);
	return res;
}
