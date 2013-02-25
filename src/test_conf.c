#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include "CUnit/Basic.h"
#include "conf.h"
#include "test_conf.h"

#define CONF_TEST_PATH "build/sample.conf"
#define CONF_TEST_FILE "SRV12:1:2\nSRV34:3:4\nSRV56:5:6\nSRV78:a:-1"


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
	service* srv = conf_parse_row("a:b:c");

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
	service_list* list = conf_parse_file(path);

	CU_ASSERT_PTR_NOT_NULL_FATAL(list);
	CU_ASSERT_EQUAL(list->count, 4);

	service* srv = service_list_lookup(list, "SRV12");
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
