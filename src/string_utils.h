#ifndef STRING_UTILS_H
#define STRING_UTILS_H

typedef struct string_words {
	char **words;
	unsigned int count;
} string_words_t;

string_words_t* string_words_new(void);
void            string_words_free(string_words_t*);
void            string_words_append(string_words_t*, const char*);
int             string_words_insert(string_words_t*, const char*, unsigned int);
string_words_t* string_split(const char*, const char*);

#endif
