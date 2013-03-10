#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/* Words wraping structure defitition */
typedef struct string_words {
	char **words;
	unsigned int count;
} string_words_t;

/* Returns a pointer to a new string_words_t structure. */
string_words_t* string_words_new(void);


/* Frees a string_words_t pointer structure. */
void            string_words_free(string_words_t*);

/* Appends a word to a string_words_t */
void            string_words_append(string_words_t*, const char*);

/* Inserts a word in a string_words_t */
int             string_words_insert(string_words_t*, const char*, unsigned int);

/* Splits a string on a delimiter into a string_words_t structure */
string_words_t* string_split(const char*, const char*);

#endif
