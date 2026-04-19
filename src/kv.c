#include <kv.h>
#include <string.h>

size_t hash(const char *value, int capacity)
{
	size_t hash = 0x13371337deadbeef;

	while (*value) {
		hash ^= *value;
		hash = hash << 8;
		hash += *value;

		value++;
	}

	return hash % capacity;
}

// func kb_put
// params:
//	- db: pointer to database
//	- key: pointer to a key value
//	- value: pointer to the value
// returns: 
//	the index of the key, otherwise on error, 
//	returns EXIT_FAILURE, on not found returns ERR_NOT_FOUND
int kv_put(kv_t *db, const char *key, const char *value)
{
	if (!db || !key || !value) return ERR_NULL_PASSED;

	size_t idx = hash(key, db->capacity);
	for (int i = 0; i < db->capacity - 1; i++) {
		size_t real_idx = (idx + i) % db->capacity;
		kv_entry_t *entry = &db->entries[real_idx];

		// the key is already set, updating
		if (entry->key && entry->key != TOMBSTONE && !strcmp(entry->key, key)) {
			char *newval = strdup(value);
			if (!newval) return ERR_NULL_PASSED;
			entry->value = newval;
			return real_idx;
		}

		// the slot is EMPTY or was removed and now TOMBSTONE
		if (!entry->key || entry->key == TOMBSTONE) {
			char *newkey = strdup(key);
			char *newval = strdup(value);
			if (!newkey | !newval) {
				free(newkey);
				free(newval);
				return ERR_NULL_PASSED;
			}
			entry->key = newkey;
			entry->value = newval;
			db->count++;
			return real_idx;
		}
	}

	// db is occupied
	return ERR_NOT_FOUND;
}

kv_t *kv_init(size_t capacity)
{
	if (capacity == 0)
		return NULL;

	kv_t *table = malloc(sizeof(kv_t));
	if (table == NULL)
	{
		return NULL;
	}

	table->capacity = capacity;
	table->count = 0;

	table->entries = calloc(sizeof(kv_entry_t), capacity);
	if (table->entries == NULL)
	{
		return NULL;
	}

	return table;
}

// TODO: implement
// char *kv_get(kv_t *db, const char *key) {}

// TODO: implement
// int kv_delete(kv_t *db, const char *key) {}

// TODO: implement
// void kv_free(kv_t *db) {}
