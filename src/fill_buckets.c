/**
 *@file fill_buckets.c
 @brief This function adds new nodes to hashtable by calculating the hashindex and adding it to a list
 *@author John Bryan Valle
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"
#include "../inc/stack.h"
#include "../inc/append.h"
#include "../inc/insert.h"

/**
 *@brief This function serves as a personalized version of he pow() function of the math lib
 *@param[in] base Base Number
 *@param[exp] exp Exponent
 *@return result Return the result of base ^ exp
 */
uint64_t pow_t(int base, int exp){

    ///1. Initialize result variable
    uint64_t result = 1;

    ///2. Catch zero exponent return 1
    if(exp == 0)return 1;

    ///3. Error catch negative exp, in this application neg exp not required
    if(exp < 0)return -1;

    ///4. Multiply base with itself exp times
    for(int i = 0; i < exp; i++){
        result *= (uint64_t)base;
    }

    ///5. Return resulting value
    return result;
}
/**
 *Generates hashindex depending on word
 * Formular: `hash_index = word[i] * k ^ i `
 * @param[in] word Assigned Word per Node
 * @param[in] hash_limit size of hashmap array
 * @parma[out] hash_index resulting hashindex between 0 - hashlimit
 */
int hash_index(char *word, int hash_limit){

    ///1. Initialize hash_value variable
    uint64_t hash_value = 0;
    int hash_const = 13;

    ///2. Iterate through letters and perform formular
    for(int i = 0; word[i] != '\0'; i++){

        hash_value += word[i] * pow_t(hash_const, i);
    }

    ///3. Return forumlar
    return hash_value%hash_limit;
}
/**
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
    if(ptr == NULL || strcmp(ptr->word, new->word)>=0){

        new->next = *head;
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

/**
 *@brief Populates buckets of all the words within the input stream
 *@param[in] buckets Hashtable
 *@param[in] hash_limit Limit of Hashtable
 *@param[in] input_stream Input stream of input file to be analyzed
 */
void fill_buckets(node_t **buckets, int hash_limit, FILE *input_stream){


    char buff[100];
    char *token;char delimiter[] = " .\n;:,?\t";

    ///1. Read every line of Input file
    while(fgets(buff,sizeof(buff),input_stream)!=NULL){

        ///2. Parse every word seperated by delimiter
        token = strtok(buff, delimiter);

        while(token!=NULL){

            ///3. Add Word to linked list of given bucket of calculated hashindex
            add_node(&buckets[hash_index(token, hash_limit)], token);

            token = strtok(NULL, delimiter);
        }

        ///4. Reset Buffer to save line
        for(int i = 0; i < 100; i++)buff[i]='\0';
    }


}
