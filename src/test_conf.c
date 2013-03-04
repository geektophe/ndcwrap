#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>
#include "CUnit/Basic.h"
#include "conf.h"
#include "test_conf.h"

#define CONF_TEST_ENVVAR "TEST_CONF_PATH"
#define CONF_TEST_PATH   "build/sample.conf"
#define CONF_TEST_PATH2  "build/sample2.conf"
#define CONF_TEST_FILE   "SRV12:1:2\nSRV34:3:4\nSRV56:5:6\nSRV78:a:-1"


void test_conf_get_path(void) {
	char* path;
	path = conf_get_path("", NULL);
	CU_ASSERT_PTR_NULL(path);

	unlink(CONF_TEST_PATH);
	FILE* fp = fopen(CONF_TEST_PATH, "w");
	CU_ASSERT_PTR_NOT_NULL_FATAL(fp);
	fclose(fp);

	path = conf_get_path(CONF_TEST_PATH, NULL);
	CU_ASSERT_STRING_EQUAL(CONF_TEST_PATH, path);

	unsetenv(CONF_TEST_ENVVAR);
	path = conf_get_path(CONF_TEST_PATH, CONF_TEST_ENVVAR);
	CU_ASSERT_STRING_EQUAL(CONF_TEST_PATH, path);

	setenv(CONF_TEST_ENVVAR, CONF_TEST_PATH2, 1);
	unlink(CONF_TEST_PATH2);
	path = conf_get_path(CONF_TEST_PATH2, CONF_TEST_ENVVAR);
	CU_ASSERT_PTR_NULL(path);

	fp = fopen(CONF_TEST_PATH2, "w");
	CU_ASSERT_PTR_NOT_NULL_FATAL(fp);
	fclose(fp);

	path = conf_get_path(CONF_TEST_PATH, CONF_TEST_ENVVAR);
	CU_ASSERT_STRING_EQUAL(CONF_TEST_PATH2, path);
}


void test_conf_check_row(void) {
	CU_ASSERT_FALSE(conf_check_row("abc"));
	CU_ASSERT_FALSE(conf_check_row("a:bc"));
	CU_ASSERT_FALSE(conf_check_row("ab:c"));
	CU_ASSERT_FALSE(conf_check_row("abc:"));
	CU_ASSERT_FALSE(conf_check_row("a:b:c:"));
	CU_ASSERT_FALSE(conf_check_row(NULL));

	CU_ASSERT_TRUE(conf_check_row("a:b:c"));
	CU_ASSERT_TRUE(conf_check_row("A:B:C"));
	CU_ASSERT_TRUE(conf_check_row("A:B:1"));
	CU_ASSERT_TRUE(conf_check_row("A:1:2"));
	CU_ASSERT_TRUE(conf_check_row("A:-1:-2"));
	CU_ASSERT_TRUE(conf_check_row("1:2:3"));
}


void test_conf_parse_row(void) {
	service_t* srv = conf_parse_row("a:b:c");

	CU_ASSERT_PTR_NOT_NULL_FATAL(srv);
	CU_ASSERT_STRING_EQUAL(srv->serv, "a");
	CU_ASSERT_STRING_EQUAL(srv->warn, "b");
	CU_ASSERT_STRING_EQUAL(srv->crit, "c");

	service_free(srv);

	srv = conf_parse_row("abc");
	CU_ASSERT_PTR_NULL(srv);
}


void test_conf_parse_file(void) {
	/* Writes test content in test configuration file */
	char path[256] = CONF_TEST_PATH;
	// printf("%s", __FILE__);
	// sprintf(path, "%s/../%s", dirname(__FILE__), CONF_TEST_PATH);
	// sprintf(path, "%s/../%s", dirname(__FILE__), CONF_TEST_PATH);

	FILE *fp = fopen(path, "w");

	if (NULL == fp) {
		perror("fopen()");
		CU_FAIL("could not create test config file");
		return;
	}

	int octets = fprintf(fp, "%s", CONF_TEST_FILE);

	if (octets != strlen(CONF_TEST_FILE)) {
		CU_FAIL("test content could not be copied in test file");
		return;
	}
	fclose(fp);

	/* Tests parsed configuration */
	service_list_t* list = conf_parse_file(path);

	CU_ASSERT_PTR_NOT_NULL_FATAL(list);
	CU_ASSERT_EQUAL(list->count, 4);

	service_t* srv = service_list_lookup(list, "SRV12");
	CU_ASSERT_PTR_NOT_NULL_FATAL(srv);
	CU_ASSERT_STRING_EQUAL(srv->warn, "1");
	CU_ASSERT_STRING_EQUAL(srv->crit, "2");

	srv = service_list_lookup(list, "SRV34");
	CU_ASSERT_PTR_NOT_NULL_FATAL(srv);
	CU_ASSERT_PTR_NOT_NULL(srv);
	CU_ASSERT_STRING_EQUAL(srv->warn, "3");
	CU_ASSERT_STRING_EQUAL(srv->crit, "4");

	srv = service_list_lookup(list, "SRV56");
	CU_ASSERT_PTR_NOT_NULL_FATAL(srv);
	CU_ASSERT_STRING_EQUAL(srv->warn, "5");
	CU_ASSERT_STRING_EQUAL(srv->crit, "6");

	srv = service_list_lookup(list, "SRV78");
	CU_ASSERT_PTR_NOT_NULL_FATAL(srv);
	CU_ASSERT_STRING_EQUAL(srv->warn, "a");
	CU_ASSERT_STRING_EQUAL(srv->crit, "-1");

	service_list_free(list);
}
