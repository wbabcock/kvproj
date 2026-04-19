#include <stdlib.h>
#include <stdio.h>
#include <kv.h>

int main(void)
{
	kv_t *table = kv_init(1024);
	printf("%p\n", (void *)table);
	printf("%zu\n", table->capacity);

	kv_put(table, "hehe", "haha");
	kv_put(table, "hehe", "hoho");
	kv_put(table, "lala", "hoho");

	for (size_t i = 0; i < table->capacity; i++) {
		if (table->entries[i].key) {
			printf("[%zu] %s: %s\n", i, table->entries[i].key, table->entries[i].value);
		}
	}

	return EXIT_SUCCESS;
}
