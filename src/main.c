/**
 *@file main.c
 * `main.c` main entry point for hashcount program
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"
#include "../inc/free_buckets.h"
#include "../inc/stack.h"
#include "../inc/append.h"
#include "../inc/insert.h"
#include "../inc/add_node.h"
#include "../inc/hash_index.h"



/**
 *Sorts words of buckets alphabetically
*
* @param[in] buckets 
* @param[in] hash_limit
 */
void display_list(node_t **buckets, int hash_limit){


    for(int i = 0; i < hash_limit; i++){
    
        node_t *ptr = buckets[i];

        for(;ptr != NULL; ptr = ptr->next){

            printf("%d: %s \n", i, ptr->word);
        }
    }
}




int main(void){

    ///1. Init `buckets` array of nodes
    int hash_limit = 40;

    node_t *buckets[40];

    for(int i = 0; i < hash_limit; i++)buckets[i] = NULL;


    buckets[hash_index("House", hash_limit)] = NULL;
 
    add_node(&buckets[hash_index("House", hash_limit)], "House");

    add_node(&buckets[hash_index("House", hash_limit)], "Robot");

    add_node(&buckets[hash_index("House", hash_limit)], "Climbing");

    add_node(&buckets[hash_index("House", hash_limit)], "Tree");

    add_node(&buckets[hash_index("House", hash_limit)], "Building");

    add_node(&buckets[hash_index("House", hash_limit)], "Curry");

    
    display_list(buckets, 40);

    for(int i = 0; i < hash_limit; i++)free_buckets(buckets[i]);

    return 0;
}


