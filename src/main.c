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


#define COLOR "\033[0;94m"
#define RESET "\033[0m"

/**
 *Sorts words of buckets alphabetically
*
* @param[in] buckets 
* @param[in] hash_limit
 */
void display_list(node_t **buckets, int hash_limit){


    for(int i = 0; i < hash_limit; i++){
    
        node_t *ptr = buckets[i];
        
        printf("\n[%2d]: ", i);
        for(int j = 1; ptr != NULL; ptr = ptr->next, j++){

            if(ptr->occurance > 1){
                printf(COLOR);
                printf("%s(%d), ",ptr->word, ptr->occurance);
                printf(RESET);
            }else printf("%s, ",ptr->word);

            if((j%10)==0)printf("\n");
        }
    }
}




int main(void){
    
    ///1. Init `buckets` array of nodes
    int hash_limit = 40;
    node_t *buckets[40];

    for(int i = 0; i < hash_limit; i++)buckets[i] = NULL;

    //=================================================
    // infuse buckets with input words
    //=================================================

    FILE *input_stream = fopen("input.txt", "r");
    FILE *output_stream = fopen("output.txt", "wb+");

    char buff[100];
    char *token;char delimiter[] = " .\n;:,?\t";

    while(fgets(buff,sizeof(buff),input_stream)!=NULL){

        token = strtok(buff, delimiter);
        
        while(token!=NULL){
            
            printf("\n%s", token);
            add_node(&buckets[hash_index(token, hash_limit)], token);
            fprintf(output_stream, "%s\n", token); 
            
            token = strtok(NULL, delimiter);
        } 
        printf("\n");
        
        for(int i = 0; i < 100; i++)buff[i]='\0';
    }
    //Close input and output streams
    fclose(input_stream);input_stream = NULL;
    fclose(output_stream);output_stream = NULL;
        
    display_list(buckets, 40);


    //=================================================
    // Select buckets and output new textfile
    //=================================================



    //=================================================
    // free all nodes
    //=================================================


    for(int i = 0; i < hash_limit; i++)free_buckets(buckets[i]);

    return 0;
}


