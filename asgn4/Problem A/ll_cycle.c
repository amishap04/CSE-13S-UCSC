#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    if (head == NULL || head->next == NULL) {
        return 0; // No cycle if the list is empty or has only one node
    }

    struct node *slow_ptr = head;
    struct node *fast_ptr = head;

    while (fast_ptr != NULL && fast_ptr->next != NULL) {
        slow_ptr = slow_ptr->next;          // Move slow pointer by 1 node
        fast_ptr = fast_ptr->next->next;    // Move fast pointer by 2 nodes

        if (slow_ptr == fast_ptr) {
            return 1; // Cycle found
        }
    }

    return 0; // No cycle found
}
}
