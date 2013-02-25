#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "argparse.h"
#include "arg.h"
#include "error.h"
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


arg* argparse_parse_arg(const char* strarg) {
	// Row format should be DYN:NAME:WARN:DEFAULT
	// Counts the number of words using ":" as separator
	string_words* parsed = string_split(strarg, ARGPARSE_DELIM);

	if (NULL == parsed) {
		PERROR();
	}

	char **words = parsed->words;
	arg* parsed_arg = NULL;

	if ( 4 == parsed->count &&
	    (0 == strncmp(words[2],"WARN",4) || 0 == strncmp(words[2],"CRIT",4))
	    ) {
		parsed_arg = arg_new();
		criticity level = LEVEL_NULL;

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
