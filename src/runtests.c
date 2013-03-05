/* Tests service related functions behaviours */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "runtests.h"
#include "test_string_utils.h"
#include "test_service.h"
#include "test_conf.h"
#include "test_arg.h"
#include "test_argparse.h"
#include "test_string_utils.h"


int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main(void) {
	CU_pSuite tsuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	tsuite = CU_add_suite("String_utils_suite", init_suite, clean_suite);
	if (NULL == tsuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(tsuite, "test of strirg_new()", test_string_new) ||
	    NULL == CU_add_test(tsuite, "test of strirg_append()", test_string_append) ||
	    NULL == CU_add_test(tsuite, "test of strirg_insert()", test_string_insert) ||
	    NULL == CU_add_test(tsuite, "test of strirg_split()", test_string_split)
	    ) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	tsuite = CU_add_suite("Service_suite", init_suite, clean_suite);
	if (NULL == tsuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(tsuite, "test of service_new()", test_service_new) ||
	    NULL == CU_add_test(tsuite, "test of service_set()", test_service_set) ||
	    NULL == CU_add_test(tsuite, "test of service_list_new()", test_service_list_new) ||
	    NULL == CU_add_test(tsuite, "test of service_list_append()", test_service_list_append) ||
	    NULL == CU_add_test(tsuite, "test of service_list_lookup()", test_service_list_lookup)
	    ) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	tsuite = CU_add_suite("Conf_suite", init_suite, clean_suite);
	if (NULL == tsuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(tsuite, "test of conf_check_row()", test_conf_check_row) ||
	    NULL == CU_add_test(tsuite, "test of conf_parse_row()", test_conf_parse_row) ||
	    NULL == CU_add_test(tsuite, "test of conf_parse_file()", test_conf_parse_file)
	    ) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	tsuite = CU_add_suite("Arg_suite", init_suite, clean_suite);
	if (NULL == tsuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(tsuite, "test of arg_new()", test_arg_new) ||
	    NULL == CU_add_test(tsuite, "test of arg_set()", test_arg_set)
	    ) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	tsuite = CU_add_suite("Argparse_suite", init_suite, clean_suite);
	if (NULL == tsuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(tsuite, "test of argparse_is_dynamic()", test_argparse_is_dynamic) ||
	    NULL == CU_add_test(tsuite, "test of argparse_parse_arg()", test_argparse_parse_arg) ||
	    NULL == CU_add_test(tsuite, "test of argparse_get_thr()", test_argparse_get_thr)
	    ) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	//CU_console_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
