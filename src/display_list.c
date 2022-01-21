/**
 *@file display_list.c
 *@author John Bryan Valle
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#include "../inc/node_t.h"

#define COLOR "\033[0;94m"
#define RESET "\033[0m"

/**
*@brief Display each element of buckets
* @param[in] buckets Hashtable of words
* @param[in] hash_limit Limit of hashtable size
* @param[in] output_stream Outputfile buckets are written to
 */
void display_list(node_t **buckets, FILE *output_stream, int hash_limit){

    ///1. Itterate through al buckets
    for(int i = 0; i < hash_limit; i++){
    
        ///2. Set Header Element of each list
        node_t *ptr = buckets[i];
        
        printf("\n[%2d]: ", i);
        fprintf(output_stream, "\n[%2d]: ", i);

        ///3. Travers through all elements of the lst
        for(int j = 1; ptr != NULL; ptr = ptr->next, j++){

            if(ptr->occurance > 1){
                printf(COLOR);
                printf("%s(%d), ",ptr->word, ptr->occurance);
                fprintf(output_stream, "%s(%d), ",ptr->word, ptr->occurance);
                printf(RESET);
            }else{
                printf("%s, ",ptr->word);
                fprintf(output_stream, "%s, ",ptr->word);
            }

            if((j%10)==0){
                printf("\n");
                fprintf(output_stream, "\n");
            }
        }
    }
}


