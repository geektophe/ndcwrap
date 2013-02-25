#include "CUnit/Basic.h"
#include "test_string_utils.h"
#include "string_utils.h"


void test_string_new(void) {
	string_words* words = string_words_new();

	CU_ASSERT_PTR_NOT_NULL_FATAL(words);
	CU_ASSERT_PTR_NULL(words->words);
	CU_ASSERT_EQUAL(words->count, 0);
}


void test_string_append(void) {
	string_words* words = string_words_new();

	CU_ASSERT_PTR_NOT_NULL_FATAL(words);

	string_words_append(words, "a");
	string_words_append(words, "b");
	string_words_append(words, "c");

	CU_ASSERT_EQUAL(words->count, 3);
	CU_ASSERT_STRING_EQUAL(words->words[0], "a");
	CU_ASSERT_STRING_EQUAL(words->words[1], "b");
	CU_ASSERT_STRING_EQUAL(words->words[2], "c");
}


void test_string_split(void) {
	char* teststr1 = "a:b:c:d";
	char* teststr2 = ":b:c:d";
	char* teststr3 = "a:b:c:";
	char* teststr4 = ":b:";
	char* teststr5 = ":";
	char* teststr6 = "a";

	string_words* words1 = string_split(teststr1, ":");
	CU_ASSERT_PTR_NOT_NULL_FATAL(words1);
	CU_ASSERT_PTR_NOT_NULL_FATAL(words1->words);
	CU_ASSERT_EQUAL(words1->count, 4);
	CU_ASSERT_STRING_EQUAL(words1->words[0], "a");
	CU_ASSERT_STRING_EQUAL(words1->words[1], "b");
	CU_ASSERT_STRING_EQUAL(words1->words[2], "c");
	CU_ASSERT_STRING_EQUAL(words1->words[3], "d");
	string_words_free(words1);

	string_words* words2 = string_split(teststr2, ":");
	CU_ASSERT_PTR_NOT_NULL_FATAL(words2);
	CU_ASSERT_PTR_NOT_NULL_FATAL(words2->words);
	CU_ASSERT_EQUAL(words2->count, 4);
	CU_ASSERT_STRING_EQUAL(words2->words[0], "");
	CU_ASSERT_STRING_EQUAL(words2->words[1], "b");
	CU_ASSERT_STRING_EQUAL(words2->words[2], "c");
	CU_ASSERT_STRING_EQUAL(words2->words[3], "d");
	string_words_free(words2);

	string_words* words3 = string_split(teststr3, ":");
	CU_ASSERT_PTR_NOT_NULL_FATAL(words3);
	CU_ASSERT_PTR_NOT_NULL_FATAL(words3->words);
	CU_ASSERT_EQUAL(words3->count, 4);
	CU_ASSERT_STRING_EQUAL(words3->words[0], "a");
	CU_ASSERT_STRING_EQUAL(words3->words[1], "b");
	CU_ASSERT_STRING_EQUAL(words3->words[2], "c");
	CU_ASSERT_STRING_EQUAL(words3->words[3], "");
	string_words_free(words3);

	string_words* words4 = string_split(teststr4, ":");
	CU_ASSERT_PTR_NOT_NULL_FATAL(words4);
	CU_ASSERT_PTR_NOT_NULL_FATAL(words4->words);
	CU_ASSERT_EQUAL(words4->count, 3);
	CU_ASSERT_STRING_EQUAL(words4->words[0], "");
	CU_ASSERT_STRING_EQUAL(words4->words[1], "b");
	CU_ASSERT_STRING_EQUAL(words4->words[2], "");
	string_words_free(words4);

	string_words* words5 = string_split(teststr5, ":");
	CU_ASSERT_PTR_NOT_NULL_FATAL(words5);
	CU_ASSERT_PTR_NOT_NULL_FATAL(words5->words);
	CU_ASSERT_EQUAL(words5->count, 2);
	CU_ASSERT_STRING_EQUAL(words5->words[0], "");
	CU_ASSERT_STRING_EQUAL(words5->words[1], "");
	string_words_free(words5);

	string_words* words6 = string_split(teststr6, ":");
	CU_ASSERT_PTR_NOT_NULL_FATAL(words6);
	CU_ASSERT_PTR_NOT_NULL_FATAL(words6->words);
	CU_ASSERT_EQUAL(words6->count, 1);
	CU_ASSERT_STRING_EQUAL(words6->words[0], "a");
	string_words_free(words6);
}
