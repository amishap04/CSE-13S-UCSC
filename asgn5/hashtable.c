#include "hashtable.h"
#include "set.h"
#include <stdlib.h>
#include <string.h>

typedef struct hashtable {
    int num_slots;
    set_t **sets;
} hashtable_t;

hashtable_t *hashtable_new(const int num_slots) {
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        return NULL;
    }

    ht->num_slots = num_slots;
    ht->sets = malloc(num_slots * sizeof(set_t*));
    if (ht->sets == NULL) {
        free(ht);
        return NULL;
    }

    for (int i = 0; i < num_slots; i++) {
        ht->sets[i] = set_new();
        if (ht->sets[i] == NULL) {
            // Handle partial allocation
            for (int j = 0; j < i; j++) {
                set_delete(ht->sets[j], NULL);
            }
            free(ht->sets);
            free(ht);
            return NULL;
        }
    }

    return ht;
}

// A simple hash function for strings
static int hash(const char *key, int num_slots) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % num_slots;
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht == NULL || key == NULL || item == NULL) {
        return false;
    }

    int index = hash(key, ht->num_slots);
    if (set_find(ht->sets[index], key) != NULL) {
        return false;
    }

    char *key_copy = strdup(key);
    if (key_copy == NULL) {
        return false;
    }

    if (!set_insert(ht->sets[index], key_copy, item)) {
        free(key_copy);
        return false;
    }

    return true;
}

void *hashtable_find(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    int index = hash(key, ht->num_slots);
    return set_find(ht->sets[index], key);
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (ht == NULL || fp == NULL || itemprint == NULL) {
        return;
    }

    for (int i = 0; i < ht->num_slots; i++) {
        set_print(ht->sets[i], fp, itemprint);
    }
}

void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht == NULL || itemfunc == NULL) {
        return;
    }

    for (int i = 0; i < ht->num_slots; i++) {
        set_iterate(ht->sets[i], arg, itemfunc);
    }
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
    if (ht == NULL) {
        return;
    }

    for (int i = 0; i < ht->num_slots; i++) {
        set_delete(ht->sets[i], itemdelete);
    }
    free(ht->sets);
    free(ht);
}
