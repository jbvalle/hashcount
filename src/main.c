/**
 *@file main.c
 * `main.c` main entry point for hashcount program
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/**
 * `node_t` linked list bucket element with 
 *  word elements
 */
typedef struct node{

    char word[15];
    struct node *next;
}node_t;

/**
 *Appends data to node of buckets
 *@param[in] head head node element of list to append data
 *@param[in] word element of node
 * */
void append(node_t **head, char *word){

    ///1. assign head to temporary ptr element
    node_t *ptr = *head;

    ///2. Init new Element with assigned values to new element
    node_t *new_element = (node_t *)malloc(sizeof(node_t));
    strcpy(new_element->word, word);
    new_element->next = NULL;

    ///3. If head element is a null pointer assign new element
    if(ptr == NULL){

        *head = new_element;
        return;
    }

    ///4. Traverse through list until Null Pointer is found
    for(;ptr->next != NULL; ptr = ptr->next);

    ///5. Assign new Element to Null Pointer
    ptr->next = new_element;

    free(new_element);
}

/**
 * `pow_t` serves as an alternative to pow() from math library
 * @param[in] base Base
 * @param[in] exp Power
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
    return hash_value%hash_limit + 1;
}


/**
 *Sorts words of buckets alphabetically
 */
void sort_words(node_t **buckets, int hash_limit){

    for
    for(int i = 0; i < hash_limit; i++){}

}



int main(void){

    ///1. Init `buckets` array of nodes
    int hash_limit = 40;

    node_t *buckets[40];

    for(int i = 0; i < hash_limit; i++)buckets[i] = NULL;
    
 
    append(&buckets[hash_index("House", hash_limit)], "House");

    append(&buckets[hash_index("House", hash_limit)], "Car");

    append(&buckets[hash_index("Climbing", hash_limit)], "Climbing");



    return 0;
} 
