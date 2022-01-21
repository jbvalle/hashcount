#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"
/**
 *@file stack.c
 *@brief Stacks new element unto list
 *@param[in] head head Reference of Hash table
 *@param[in] word String Member of element
 */
void stack(node_t **head, char *word){

    node_t *ptr = *head;

    node_t *new = (node_t *)malloc(sizeof(node_t));
    strcpy(new->word, word);
    new->occurance = 1;
    new->next = NULL;

    if(ptr == NULL){

        *head = new;
        return;
    }

    new->next = *head;
    *head = new;
}
