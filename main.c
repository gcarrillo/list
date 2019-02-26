#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "list.h"

#define NUM_ELS 10
#define MASK ((1 << 8) - 1)

struct my_obj {
	uint64_t key;
};

static int
obj_compar(const void *d1, const void *d2)
{
	const int *key1 = d1;
	const int *key2 = d2;

	if (*key1 < *key2)
		return -1;
	else if (*key1 > *key2)
		return 1;
	else
		return 0;
}

static void
print_obj(void *data)
{
	struct my_obj *o = data;
	printf("o->key = %"PRIu64"\n", o->key);
}

static bool
test_split(void *arg, void *data)
{
	uint64_t *split_key = arg;
	struct my_obj *o = data;

	if (o->key > *split_key)
		return true;

	return false;
}

static void
free_obj(void *data)
{
	struct my_obj *o = data;
	free(o);
}

int
main(int argc, char **argv)
{
	struct my_obj *o;
	struct list *l;
	struct list *run_list;
	uint64_t split_key;
	int ret;
	int i;

	l = list_new();

	for (i = 0; i < NUM_ELS; i++) {
		o = malloc(sizeof(*o));
		if (!o) {
			printf("failed to allocate timer memory\n");
			exit(EXIT_FAILURE);
		}

		o->key = (uint64_t)(rand() & MASK);

		ret = list_insert(l, o, obj_compar);
		if (ret < 0)
			printf("Failed to insert item into list\n");
	}

	list_apply(l, print_obj);

	split_key = (uint64_t)(rand() & MASK);
	list_split(l, &run_list, test_split, (void *)&split_key);

	printf("\nsplit_key = %"PRIu64"\n\n", split_key);

	printf("original list:\n");
	list_apply(l, print_obj);

	printf("\nrun list:\n");
	list_apply(run_list, print_obj);

	list_free(l, free_obj);
	list_free(run_list, free_obj);

	return 0;
}
