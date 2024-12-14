/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/utils.h"
#include "./list.h"

static size_t list_size;

void list_init_head(struct int_list *head)
{
	head->item = HEAD_ITEM;
	head->next = head;
	head->prev = head;

	list_size = 0;
}

void list_add_item(struct int_list *head, int item)
{
	struct int_list *p;

	p = malloc(sizeof(*p));
	DIE(p == NULL, "malloc");
	p->item = item;

	p->next = head->next;
	p->prev = head;
	head->next->prev = p;
	head->next = p;

	list_size++;
}

void list_add_item_tail(struct int_list *head, int item)
{
	struct int_list *p;

	p = malloc(sizeof(*p));
	DIE(p == NULL, "malloc");
	p->item = item;

	p->next = head;
	p->prev = head->prev;
	head->prev->next = p;
	head->prev = p;

	list_size++;
}

void list_insert_item(struct int_list *head, size_t pos, int item)
{
	struct int_list *p, *place;
	size_t i;

	/*
	 * Find place to insert item.
	 * If pos is greater than list size insert after head.
	 */

	place = head->next;
	for (i = 0; i < pos; i++) {
		if (place == head)
			break;
		place = place->next;
	}

	p = malloc(sizeof(*p));
	DIE(p == NULL, "malloc");
	p->item = item;

	p->next = place->next;
	p->prev = place;
	place->next->prev = p;
	place->next = p;

	list_size++;
}

void list_remove_item(struct int_list *head, size_t pos)
{
	struct int_list *p;
	size_t i;

	/* Cannot remove item outside of list. */
	if (pos >= list_size)
		return;

	p = head->next;
	for (i = 0; i < pos; i++) {
		/* Something fishy happened if head was reached. */
		if (p == head) {
			fprintf(stderr, "reached head when removing. not good.\n");
			break;
		}
		p = p->next;
	}

	p->prev->next = p->next;
	p->next->prev = p->prev;
	p->prev = p->next = p;
	free(p);

	list_size--;
}

int list_search_item(struct int_list *head, int item)
{
	struct int_list *p;

	for (p = head->next; p != head; p = p->next) {
		if (p->item == item)
			return 1;
		if (p == head)
			break;
	}

	return 0;
}

size_t list_get_size(struct int_list *head)
{
	return list_size;
}
