#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#include "../inc/node_t.h"

#define COLOR "\033[0;94m"
#define RESET "\033[0m"

/**
 *Sorts words of buckets alphabetically
*
* @param[in] buckets 
* @param[in] hash_limit
 */
void display_list(node_t **buckets, FILE *output_stream, int hash_limit){


    for(int i = 0; i < hash_limit; i++){
    
        node_t *ptr = buckets[i];
        
        printf("\n[%2d]: ", i);
        fprintf(output_stream, "\n[%2d]: ", i);
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


