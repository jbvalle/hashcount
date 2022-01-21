#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"

/**
 *@file insert.c
 *@brief Insertion new Element after element with key as string member
 *@param[in] head head reference
 *@param[in] key Preceding String member of list element
 *@param[in] new_key New String member of list element
 */
void insert(node_t **head, char *key, char *new_key){

    node_t *ptr = *head;

    node_t *new = (node_t *)malloc(sizeof(node_t));
    strcpy(new->word, new_key);
    new->occurance = 1;
    new->next = NULL;

    for(; ptr != NULL; ptr = ptr->next){

        if(strcmp(ptr->word, key) == 0){

            new->next = ptr->next;
            ptr->next = new;
            return;
        }
    }

}
