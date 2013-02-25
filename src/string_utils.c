#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "string_utils.h"


string_words* string_words_new(void) {
	string_words* new_string_words = (string_words*)malloc(sizeof(string_words));

	if (NULL == new_string_words) {
		PERROR();
	}
	new_string_words->words = NULL;
	new_string_words->count = 0;
	return new_string_words;
}


void string_words_free(string_words* target) {
	if (NULL == target)
		return;

	unsigned int i = 0;

	for (i=0; i<target->count; i++) {
		if (NULL != target->words[i]) {
			free(target->words[i]);
			target->words[i] = NULL;
		}
	}

	/* Frees serv field */
	if (NULL != target->words) {
		free(target->words);
		target->words = NULL;
	}
	target->count = 0;

	/* Frees object memory */
	free(target);
}


void string_words_append(string_words* target, const char* word) {

	if (NULL == target) {
		ERROR("target is not initialized.", 1);
	}

	if (target->words == NULL) {
		target->words = (char**)malloc(sizeof(char*));
	} else {
		target->words = (char**)realloc(target->words, sizeof(char*) * (target->count + 1));
	}

	if (NULL == target->words) {
		PERROR();
	}

	target->words[target->count] = strdup(word);

	if (NULL == target->words[target->count]) {
		PERROR();
	}
	target->count++;
}


string_words* string_split(const char* str, const char* delim) {
	string_words* words = string_words_new();

	if (NULL == words) {
		PERROR();
	}

	char* buf = strdup(str);

	if (NULL == buf) {
		PERROR();
	}

	unsigned int i = 0;

	/* Checks if the first character is a delimiter */
	for (i=0; i<strlen(delim); i++) {
		if (delim[i] == str[0]) {
			string_words_append(words, "");
			break;
		}
	}

	/* Breaks string on delimiters into words */
	char *token = strtok(buf, delim);

	while (NULL != token) {
		string_words_append(words, token);
		token = strtok(NULL, delim);
	}

	/* Checks if the last character is a delimiter */
	for (i=0; i<strlen(delim); i++) {
		if (delim[i] == str[strlen(str) - 1]) {
			string_words_append(words, "");
			break;
		}
	}

	free(buf);
	return words;
}
