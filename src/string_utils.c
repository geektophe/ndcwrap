#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "string_utils.h"


/*
 * Returns a pointer to a new string_words_t structure.
 *
 * Caution, returned poirnter has to be freed using string_words_free function.
 *
 * @return string_words_t*
 */
string_words_t* string_words_new(void) {
	string_words_t* new_string_words =
		(string_words_t*)malloc(sizeof(string_words_t));

	if (NULL == new_string_words) {
		PERROR();
	}
	new_string_words->words = NULL;
	new_string_words->count = 0;
	return new_string_words;
}


/**
 * Frees a string_words_t structure pointer.
 *
 * @param[in] target	The string_words_t structure pointer to free.
 * @return void
 */
void string_words_free(string_words_t* target) {
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


/**
 * Appends a new word at the end of the string_words_t pointed by target.
 *
 * Note that the words attribute is always NULL terminated.
 *
 * @param[in] target	The string_words_t structure pointer to append word.
 * @param[in] word	The word to append.
 * @return void
 */
void string_words_append(string_words_t* target, const char* word) {

	if (NULL == target) {
		ERROR("target is not initialized.", 1);
	}

	if (target->words == NULL) {
		target->words = (char**)malloc(sizeof(char*) * 2);
	} else {
		target->words = (char**)realloc(target->words, sizeof(char*) *
				(target->count + 2));
	}

	if (NULL == target->words) {
		PERROR();
	}

	target->words[target->count] = strdup(word);
	target->words[target->count+1] = NULL;

	if (NULL == target->words[target->count]) {
		PERROR();
	}
	target->count++;
}


/**
 * Inserts a new word in of the string_words_t pointed by target at a given
 * position.
 *
 * Note that the words attribute is always NULL terminated.
 *
 * @param[in] target	The string_words_t structure pointer to insert word.
 * @param[in] word	The word to insert.
 * @param[in] pos	The position to inserv word in words attribute array.
 * @return void
 */
int string_words_insert(string_words_t* target, const char* word, unsigned int pos) {

	if (NULL == target) {
		ERROR("target is not initialized.", 1);
	}

	if (pos > target->count) {
		return -1;
	}

	if (NULL == target->words) {
		target->words = (char**)malloc(sizeof(char*) * 2);
	} else {
		target->words = (char**)realloc(target->words, sizeof(char*) * (target->count + 2));
	}

	if (NULL == target->words) {
		PERROR();
	}

	unsigned int i;
	for (i=target->count; i>pos; i--) {
		target->words[i] = target->words[i-1];
	}

	target->words[pos] = strdup(word);

	if (NULL == target->words[pos]) {
		PERROR();
	}
	target->count++;
	return pos;
}


/**
 * Splits a string into words using a specified delimiter.
 *
 * Caution, returned poirnter has to be freed using string_words_free function.
 *
 * Note that the words attribute is always NULL terminated.
 *
 * @param[in] str	The string to stplit.
 * @param[in] delim	The delimiter used to split string (uses strtok).
 * @return void
 */
string_words_t* string_split(const char* str, const char* delim) {
	string_words_t* words = string_words_new();

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
