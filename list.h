#ifndef __LIST_H_
#define __LIST_H_

#include <stdbool.h>

struct node;

struct list {
	struct node *head;
};

struct list *list_new(void);
int list_insert(struct list *l, void *data,
		int (*compar_f)(const void *d1, const void *d2));
void list_apply(struct list *l, void (*apply_f)(void *data));
void list_split(struct list *l, struct list **left,
		bool (*test_f)(void *arg, void *data), void *farg);
void list_free(struct list *l, void (*free_f)(void *data));

#endif /* __LIST_H_ */
