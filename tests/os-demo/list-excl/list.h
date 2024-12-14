/*
 * Imported from the operating systems class.
 */

#ifndef TESTS_OS_DEMO_LIST_EXCL_LIST_H_
#define TESTS_OS_DEMO_LIST_EXCL_LIST_H_		1

struct int_list {
	int item;
	struct int_list *next;
	struct int_list *prev;
};

#define HEAD_ITEM		0xCCCCCCCC

void list_init_head(struct int_list *head);
void list_add_item(struct int_list *head, int item);
void list_add_item_tail(struct int_list *head, int item);
void list_insert_item(struct int_list *head, size_t pos, int item);
void list_remove_item(struct int_list *head, size_t pos);
int list_search_item(struct int_list *head, int item);
size_t list_get_size(struct int_list *head);

#endif  // TESTS_OS_DEMO_LIST_EXCL_LIST_H_
