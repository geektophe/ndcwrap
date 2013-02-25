#include <stdio.h>
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
	arg* parsed = NULL;

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
