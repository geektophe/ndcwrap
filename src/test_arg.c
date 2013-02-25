/* Tests service related functions behaviours */

#include "CUnit/Basic.h"
#include "test_arg.h"
#include "arg.h"


void test_arg_new(void) {
	arg* a = arg_new();

	CU_ASSERT_PTR_NOT_NULL_FATAL(a);
	CU_ASSERT_PTR_NULL(a->serv);
	CU_ASSERT_EQUAL(a->level, LEVEL_NULL);
	CU_ASSERT_PTR_NULL(a->deflt);

	arg_free(a);
}


void test_arg_set(void) {
	char* serv = "SRV";
	criticity level = LEVEL_WARN;
	char* deflt = "1";

	arg* a = arg_new();
	arg_set(a, serv, level, deflt);

	CU_ASSERT_PTR_NOT_NULL_FATAL(a);
	CU_ASSERT_STRING_EQUAL(a->serv, serv);
	CU_ASSERT_EQUAL(a->level, level);
	CU_ASSERT_STRING_EQUAL(a->deflt, deflt);

	arg_free(a);
}
