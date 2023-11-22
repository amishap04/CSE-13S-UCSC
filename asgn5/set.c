#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

typedef struct setnode {
    char *key;
    void *item;
    struct setnode *next;
} setnode_t;

typedef struct set {
    struct setnode *head;
} set_t;

set_t* set_new(void) {
    set_t *set = malloc(sizeof(set_t));
    if (set == NULL) {
        return NULL;
    }
    set->head = NULL;
    return set;
}

bool set_insert(set_t *set, const char *key, void *item) {
    if (set == NULL || key == NULL) {
        return false;
    }

    // Check if the key already exists
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return false;
        }
    }

    // Create a new node
    setnode_t *newnode = malloc(sizeof(setnode_t));
    if (newnode == NULL) {
        return false;
    }
    newnode->key = strdup(key);
    if (newnode->key == NULL) {
        free(newnode);
        return false;
    }
    newnode->item = item;
    newnode->next = set->head;
    set->head = newnode;

    return true;
}

void *set_find(set_t *set, const char *key) {
    if (set == NULL || key == NULL) {
        return NULL;
    }

    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return node->item;
        }
    }

    return NULL;
}

void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (fp == NULL) {
        return;
    }
    if (set == NULL) {
        fprintf(fp, "(null)\n");
    } else {
        for (setnode_t *node = set->head; node != NULL; node = node->next) {
            if (itemprint != NULL) {
                (*itemprint)(fp, node->key, node->item);
            }
        }
    }
}

void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (set == NULL || itemfunc == NULL) {
        return;
    }

    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        (*itemfunc)(arg, node->key, node->item);
    }
}

void set_delete(set_t *set, void (*itemdelete)(void *item)) {
    if (set == NULL) {
        return;
    }

    setnode_t *node = set->head;
    while (node != NULL) {
        setnode_t *next = node->next;
        if (itemdelete != NULL) {
            (*itemdelete)(node->item);
        }
        free(node->key);
        free(node);
        node = next;
    }

    free(set);
}
