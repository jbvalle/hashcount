#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/node_t.h"
/**
 *@file free_buckets.c
 *Frees all mallocs of buckets
 *
 *@param[int] buckets
 */
void free_buckets(node_t *head){

    ///1. Check for Null Pointer
    if(head == NULL)return;

    ///2. Assign head to temporary ptr
    node_t *ptr = head;

    ///3. Traverse through list until NUll pointer is found
    while(ptr != NULL){

        ///4. Assign next element to temporary ptr
        node_t *temp = ptr->next;

        ///5. Free ptr
        free(ptr);

        ///6. Reassign temporary next element to ptr
        ptr = temp;
    }
}
