#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"
#include "../inc/stack.h"
#include "../inc/append.h"
#include "../inc/insert.h"

/**
 *@file add_node.c
 *Adds new node to list using stack(), insert() and append() function
 *Add new node in alphabetical order depending in string members of elements
 *@param[in] head headreference of list
 *@param[in] new_key new string member of new node
 */
void add_node(node_t **head, char *new_key){

    ///1. Assign ptr to head reference
    node_t *ptr = *head;

    ///2. Allocate new node and assign values
    node_t *new = (node_t *)malloc(sizeof(node_t));
    strcpy(new->word, new_key);
    new->occurance = 1;
    new->next = NULL;

    ///3. Check for if Head is NULL Pointer and assign new element as new head
    if(ptr == NULL){

        *head = new;
        return;
    }
    free(new);

    ///4. Check for multiple occurances in list
    ptr = *head;

    while(ptr!=NULL){
        
        if(strcmp(ptr->word,new_key)==0){
            
            ptr->occurance += 1;
            return;
        }
        
        ptr = ptr->next;
    }



    ///5. Check if first elements string member -> correct alphabetical order, else -> stack unto list
    ptr = *head;
    if(strcmp(ptr->word, new_key) > 0){

        stack(head, new_key);
        return;
    }

    ///7. Traverse through list using ptr and stop when correct slot for new element is found according to string member
    ptr = *head;

    for(; (ptr->next != NULL)&&(strcmp(ptr->next->word, new_key) > 0); ptr = ptr->next);

    insert(head, ptr->word, new_key);

    ///8. If all preceding elements are preceding string members append new element to lost
    if(ptr == NULL)append(head, new_key);

}
