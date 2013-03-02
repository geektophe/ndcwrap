/* Tests service related functions behaviours */

#include "CUnit/Basic.h"
#include "test_service.h"
#include "service.h"


void test_service_new(void) {
	service_t* srv = service_new();

	CU_ASSERT_PTR_NOT_NULL_FATAL(srv);
	CU_ASSERT_PTR_NULL(srv->serv);
	CU_ASSERT_PTR_NULL(srv->warn);
	CU_ASSERT_PTR_NULL(srv->crit);
	CU_ASSERT_PTR_NULL(srv->next);

	service_free(srv);
}


void test_service_set(void) {
	char* name = "name";
	char* warn = "warn";
	char* crit = "crit";

	service_t* srv = service_new();

	CU_ASSERT_PTR_NOT_NULL_FATAL(srv);

	service_set(srv, name, warn, crit);

	CU_ASSERT_STRING_EQUAL(srv->serv, name);
	CU_ASSERT_STRING_EQUAL(srv->warn, warn);
	CU_ASSERT_STRING_EQUAL(srv->crit, crit);

	service_free(srv);
}


void test_service_list_new(void) {
	service_list_t* list = service_list_new();

	CU_ASSERT_PTR_NOT_NULL_FATAL(list);
	CU_ASSERT_PTR_NULL(list->first);
	CU_ASSERT_PTR_NULL(list->last);
	CU_ASSERT_EQUAL(list->count, 0);

	service_list_free(list);
}


void test_service_list_append(void) {
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

	CU_ASSERT_EQUAL(list->count, 1);
	CU_ASSERT_PTR_NOT_NULL(list->first);
	CU_ASSERT_PTR_NOT_NULL(list->last);
	CU_ASSERT_PTR_EQUAL(list->first, list->last);
	CU_ASSERT_PTR_EQUAL(srv1, list->first);

	service_list_append(list, srv2);

	CU_ASSERT_EQUAL(list->count, 2);
	CU_ASSERT_PTR_NOT_EQUAL(list->first, list->last);
	CU_ASSERT_PTR_EQUAL(srv1, list->first);
	CU_ASSERT_PTR_EQUAL(srv2, list->last);

	service_list_free(list);
}


void test_service_list_lookup(void) {
	char* name1 = "name1";
	char* warn1 = "warn1";
	char* crit1 = "crit1";

	char* name2 = "name2";
	char* warn2 = "warn2";
	char* crit2 = "crit2";

	service_t* srv1 = service_new();
	service_set(srv1, name1, warn1, crit1);
	service_t* srv2 = service_new();
	service_set(srv2, name2, warn2, crit2);

	service_list_t* list = service_list_new();
	service_list_append(list, srv1);
	service_list_append(list, srv2);

	service_t* search = service_list_lookup(list, "name1");
	CU_ASSERT_PTR_EQUAL(search, srv1);

	search = service_list_lookup(list, "name2");
	CU_ASSERT_PTR_EQUAL(search, srv2);

	search = service_list_lookup(list, "noname");
	CU_ASSERT_PTR_NULL(search);

	service_list_free(list);
}
