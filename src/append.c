/**
 *@file append.c
 *@brief Appends to last element of list
 *@author John Bryan Valle
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"

/**
 *@brief Appends to last element of list
 *@param[in] head headreference
 *@param[in] word string member to be added
 */
void append(node_t **head, char *word){

    node_t *ptr = *head;

    node_t *new = (node_t *)malloc(sizeof(node_t));
    strcpy(new->word, word);
    new->occurance = 1;
    new->next = NULL;

    if(ptr == NULL){

        *head = new;
        return;
    }

    for(; ptr->next != NULL; ptr = ptr->next);

    ptr->next = new;
}
