/**
 *@file sorting.c
 *
 *@brief This function sort individual words in alphabetical order
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "../inc/node_t.h"

/**
 *@brief This function insert new element to list in an alphabetically sorted order
 *@param[in] sorted head of sorted list
 *@param[in] new Subsequent Word in a list
 */
void sorted_insert(node_t **sorted, node_t *new){

    ///1. Checks if first element is null or if first element's word is a 'subsequent' word of new
    if((*sorted) == NULL || ( strcmp((*sorted)->word, new->word) >= 0)){

        ///2. Stack new word unto list if first element is either Null or a subsequent word 
        new->next = *sorted;
        *sorted = new;

    }else{
        
        ///3. Traverse through list until elements list is a subsequent element to new element
        node_t *curr_ptr = *sorted;

        while(curr_ptr->next != NULL && (strcmp(curr_ptr->next->word, new->word) <= 0)){
            
            curr_ptr = curr_ptr->next;
        }

        ///4. Insert new element behind the supposedly subsequent list's element
        new->next = curr_ptr->next;
        curr_ptr->next = new;
    }
}


/**
 *@brief This function traverses though list and adds any subsequent word into the sorted list
 *@param[in] head Head of current Bucket
 */

void insertionSort(node_t **head){

    ///1. Initialize head of sorted list
    node_t *sorted = NULL;

    node_t *curr_ptr = *head;

    ///2. Traverse through list and add subsequnent elements to the sorted list
    while(curr_ptr != NULL){

        node_t *temp = curr_ptr->next;

        sorted_insert(&sorted, curr_ptr);
        
        curr_ptr = temp;
    }

    ///3. Assign new head of sorted list to original head
    *head = sorted;
}

