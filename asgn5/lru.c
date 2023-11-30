#include "lru.h"
#include "hashtable.h" // Assuming you have a hashtable implementation
#include <stdlib.h>
#include <string.h>

// Node for the doubly linked list
typedef struct node {
    char *key;
    void *item;
    struct node *prev;
    struct node *next;
} node_t;

// LRU Cache structure
struct lru {
    int capacity;
    int size;
    node_t *head;
    node_t *tail;
    hashtable_t *table; // Assuming hashtable_t from previous part
};

// Utility function to create a new node
static node_t *node_new(const char *key, void *item) {
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        return NULL;
    }
    node->key = strdup(key);
    node->item = item;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Move a node to the front of the list
static void move_to_front(lru_t *lru, node_t *node) {
    if (node == lru->head) {
        return;
    }

    // Detach node from its current position
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }

    // Attach node at the front of the list
    node->prev = NULL;
    node->next = lru->head;
    if (lru->head) {
        lru->head->prev = node;
    }
    lru->head = node;

    if (lru->tail == NULL) {
        lru->tail = node;
    }
}

// Remove the least recently used item
static void remove_lru(lru_t *lru) {
    if (lru->tail == NULL) {
        return;
    }

    node_t *old_tail = lru->tail;
    lru->tail = old_tail->prev;
    if (lru->tail) {
        lru->tail->next = NULL;
}

    // hashtable_delete(lru->table, old_tail->key); 
    free(old_tail->key);
    free(old_tail);
}

lru_t *lru_new(const int capacity) {
    lru_t *lru = malloc(sizeof(lru_t));
    if (lru == NULL) {
        return NULL;
    }

    lru->capacity = capacity;
    lru->size = 0;
    lru->head = NULL;
    lru->tail = NULL;
    lru->table = hashtable_new(capacity);

    return lru;
}

bool lru_insert(lru_t *lru, const char *key, void *item) {
    if (lru == NULL || key == NULL || item == NULL) {
        return false;
    }

    void *found = hashtable_find(lru->table, key);

    if (found != NULL) {
	return false;
}

    if (lru->size >= lru->capacity) {
        // Remove least recently used item
        remove_lru(lru);
        lru->size--;
    }

    // Insert new item
    node_t *new_node = node_new(key, item);
    if (new_node == NULL) {
        return false;
    }

    move_to_front(lru, new_node);
    hashtable_insert(lru->table, key, new_node);
    lru->size++;

    return true;
}

void *lru_find(lru_t *lru, const char *key) {
    if (lru == NULL || key == NULL) {
        return NULL;
    }

    void *found = hashtable_find(lru->table, key);
    if (found != NULL) {
        // Move the found node to the front (most recently used)
        move_to_front(lru, (node_t *)found);
        return ((node_t *)found)->item;
    }

    return NULL;
}

void lru_print(lru_t *lru, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (lru == NULL || fp == NULL || itemprint == NULL) {
        return;
    }

    for (node_t *current = lru->head; current != NULL; current = current->next) {
        itemprint(fp, current->key, current->item);
    }
}

void lru_iterate(lru_t *lru, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (lru == NULL || itemfunc == NULL) {
        return;
    }

    for (node_t *current = lru->head; current != NULL; current = current->next) {
        itemfunc(arg, current->key, current->item);
    }
}

void lru_delete(lru_t *lru, void (*itemdelete)(void *item)) {
    if (lru == NULL) {
        return;
    }

    node_t *current = lru->head;
    while (current != NULL) {
        node_t *next = current->next;

        if (itemdelete != NULL) {
            itemdelete(current->item);
        }

        hashtable_delete(lru->table, itemdelete);
        free(current->key);
        free(current);

        current = next;
    }

    hashtable_delete(lru->table, NULL);
    free(lru);
}
