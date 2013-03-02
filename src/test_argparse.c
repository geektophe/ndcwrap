#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "argparse.h"
#include "arg.h"


void test_argparse_is_dynamic(void) {
	char test_arg[16] = "";

	snprintf(test_arg, 15, "%s:SRV:WARN:1", ARGPARSE_PREFIX);
	CU_ASSERT_TRUE(argparse_is_dynamic(test_arg));

	snprintf(test_arg, 15, "1");
	CU_ASSERT_FALSE(argparse_is_dynamic(test_arg));
}

void test_argparse_parse_arg(void) {
	char test_arg[33] = "";
	arg_t* parsed = NULL;

	/* Wrong criticity level */
	snprintf(test_arg, 32, "%s:SRV:NONE:1", ARGPARSE_PREFIX);
	parsed = argparse_parse_arg(test_arg);
	CU_ASSERT_PTR_NULL(parsed);

	if (NULL != parsed) {
		arg_free(parsed);
	}

	/* Missing default value */
	snprintf(test_arg, 32, "%s:SRV:WARN", ARGPARSE_PREFIX);
	parsed = argparse_parse_arg(test_arg);
	CU_ASSERT_PTR_NULL(parsed);

	if (NULL != parsed) {
		arg_free(parsed);
	}

	snprintf(test_arg, 32, "%s:SRV1:WARN:1", ARGPARSE_PREFIX);
	parsed = argparse_parse_arg(test_arg);

	CU_ASSERT_PTR_NOT_NULL_FATAL(parsed);
	CU_ASSERT_STRING_EQUAL(parsed->serv, "SRV1");
	CU_ASSERT_EQUAL(parsed->level, LEVEL_WARN);
	CU_ASSERT_STRING_EQUAL(parsed->deflt, "1");

	arg_free(parsed);

	snprintf(test_arg, 32, "%s:SRV2:CRIT:-1", ARGPARSE_PREFIX);
	parsed = argparse_parse_arg(test_arg);

	CU_ASSERT_PTR_NOT_NULL_FATAL(parsed);
	CU_ASSERT_STRING_EQUAL(parsed->serv, "SRV2");
	CU_ASSERT_EQUAL(parsed->level, LEVEL_CRIT);
	CU_ASSERT_STRING_EQUAL(parsed->deflt, "-1");

	arg_free(parsed);
}

void test_argparse_get_thr(void) {
	char* name1 = "name1";
	char* warn1 = "warn1";
	char* crit1 = "crit1";

	char* name2 = "name2";
	char* warn2 = "warn2";
	char* crit2 = "crit2";

	service_t* srv1 = service_new();
	CU_ASSERT_PTR_NOT_NULL_FATAL(srv1);
	service_set(srv1, name1, warn1, crit1);

	service_t* srv2 = service_new();
	CU_ASSERT_PTR_NOT_NULL_FATAL(srv2);
	service_set(srv2, name2, warn2, crit2);

	service_list_t* list = service_list_new();
	CU_ASSERT_PTR_NOT_NULL_FATAL(list);

	service_list_append(list, srv1);
	service_list_append(list, srv2);

	char test_arg[33] = "";
	char* thr = NULL;

	// snprintf(test_arg, 32, "%s:SRV1:WARN:1", ARGPARSE_PREFIX);

	snprintf(test_arg, 32, "1");
	thr = argparse_get_thr(list, test_arg);
	CU_ASSERT_STRING_EQUAL(thr, "1");
	free(thr);

	snprintf(test_arg, 32, "%s:name1:WARN:2", ARGPARSE_PREFIX);
	thr = argparse_get_thr(list, test_arg);
	CU_ASSERT_STRING_EQUAL(thr, "warn1");
	free(thr);

	snprintf(test_arg, 32, "%s:name1:CRIT:3", ARGPARSE_PREFIX);
	thr = argparse_get_thr(list, test_arg);
	CU_ASSERT_STRING_EQUAL(thr, "crit1");
	free(thr);

	snprintf(test_arg, 32, "%s:name2:WARN:2", ARGPARSE_PREFIX);
	thr = argparse_get_thr(list, test_arg);
	CU_ASSERT_STRING_EQUAL(thr, "warn2");
	free(thr);

	snprintf(test_arg, 32, "%s:name2:CRIT:3", ARGPARSE_PREFIX);
	thr = argparse_get_thr(list, test_arg);
	CU_ASSERT_STRING_EQUAL(thr, "crit2");
	free(thr);

	// Missing default value
	snprintf(test_arg, 32, "%s:name1:WARN", ARGPARSE_PREFIX);
	thr = argparse_get_thr(list, test_arg);
	CU_ASSERT_PTR_NULL(thr);
	free(thr);

	// Undefined service
	snprintf(test_arg, 32, "%s:noname:WARN:6", ARGPARSE_PREFIX);
	thr = argparse_get_thr(list, test_arg);
	CU_ASSERT_STRING_EQUAL(thr, "6");
	free(thr);
}
