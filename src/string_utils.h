#ifndef STRING_UTILS_H
#define STRING_UTILS_H

typedef struct string_words {
	char **words;
	unsigned int count;
} string_words;

string_words* string_words_new(void);
void string_words_free(string_words*);
void string_words_append(string_words*, const char*);
string_words* string_split(const char*, const char*);

#endif
