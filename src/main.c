#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "conf.h"
#include "argparse.h"
#include "service.h"
#include "string_utils.h"


int main(int argc, char **argv) {
	if (argc < 3) {
		char errmsg[128];
		snprintf(errmsg, 128, "usage: %s wrapped arg1 arg2 ...", argv[0]);
		error(errmsg, ECRITICAL);
	}

	char* path = conf_get_path(DCLIWRAP_CONFIG, DCLIWRAP_ENVVAR);

	if (NULL == path) {
		error("CRITICAL: Could not read configuration file.", ECRITICAL);
	}

	service_list_t* conf = conf_parse_file(path);
	string_words_t* dest = string_words_new();

	int i;
	for (i=1; i<argc; i++) {
		if (argparse_is_dynamic(argv[i])) {
			char* arg = argparse_get_thr(conf, argv[i]);
			string_words_append(dest, arg);
			free(arg);
		} else {
			string_words_append(dest, argv[i]);
		}
	}
	service_list_free(conf);

	unsigned int j;
	for (j=0; j<dest->count; j++) {
		printf("%s ", dest->words[j]);
	}
	printf("\n");
	string_words_free(dest);
	return 0;
}


void error(char* errmsg, int code) {
	fprintf(stderr, "%s\n", errmsg);
	exit(code);
}
