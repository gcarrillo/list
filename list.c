#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

struct node {
	void *data;
	struct node *next;
};

struct node *
node_new(void)
{
	struct node *n = NULL;

	n = malloc(sizeof(*n));
	memset(n, 0, sizeof(*n));

	return n;
}

struct list *
list_new(void)
{
	struct list *l = NULL;

	l = malloc(sizeof(*l));
	memset(l, 0, sizeof(*l));

	return l;
}

int
list_insert(struct list *l, void *data,
	    int (*compar)(const void *d1, const void *d2))
{
	struct node *new, *cur, **prevnext;

	new = node_new();
	new->data = data;

	cur = l->head;
	prevnext = &l->head;

	while (cur != NULL && ((*compar)(data, cur->data) > 0)) {
		prevnext = &cur->next;
		cur = cur->next;
	}

	new->next = *prevnext;
	*prevnext = new;

	return 0;
}

void
list_apply(struct list *l, void (*f)(void *data))
{
	struct node *cur;

	cur = l->head;

	while (cur != NULL) {
		(*f)(cur->data);
		cur = cur->next;
	}
}

void
list_split(struct list *l, struct list **left,
	   bool (*test_f)(void *arg, void *data), void *farg)
{
	struct node *cur, **prevnext;

	*left = list_new();
	(*left)->head = l->head;

	cur = l->head;
	prevnext = &l->head;

	while (cur != NULL && ((*test_f)(farg, cur->data) == false)) {
		prevnext = &cur->next;
		cur = cur->next;
	}

	*prevnext = NULL;
	l->head = cur;
}

void
list_free(struct list *l, void (*free_func)(void *data))
{
	struct node *cur = l->head;
	struct node *prev;

	while (cur != NULL) {
		(*free_func)(cur->data);
		prev = cur;
		cur = cur->next;
		free(prev);
	}

	free(l);
}
