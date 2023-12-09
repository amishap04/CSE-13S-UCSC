#ifndef CRAWLER_H
#define CRAWLER_H

#include <stddef.h>
//#include "set.h"
//#include "hashtable.h"

typedef struct {
	char *url;
	char *html;
	size_t length;
	int depth;
} webpage_t;

typedef struct node {
    webpage_t *page;
    struct node *next;
} node_t;


typedef struct {
    node_t *head;
    node_t *tail;
    int size;
} bag_t;

typedef struct node_h {
    char *data;
    struct node_h *next;
} node_h;


typedef struct {
    node_h *head;
} hashtable_t;

#endif
