#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"

#define COLOR "\033[0;94m"
#define RESET "\033[0m"


void choose_buckets(node_t **buckets, int *requested_index, int *chosen_flag){

    char delimiter[] = " .\n;:,?\t";
    char user_input[50], letter;
    int input_index;
    //Initialize user_input
    for(int i = 0; i < 50; i++)user_input[i] = '\0';
    
    if(chosen_flag[2]){

        printf("\n\n+-------------------------------------------------------+\n");
        printf("| Please enter desired indices of buckets to be removed |\n");
        printf("+-------------------------------------------------------+\n");
        printf("\n»");
    }

    if(!chosen_flag[2]){

        printf("\n\n+---------------------------------------------------------------------+\n");
        printf("| Please enter desired indices of buckets which should not be censored|\n");
        printf("+---------------------------------------------------------------------+\n");
        printf("\n»");
    }
    //Letterwise user input
    for(input_index = 0; (letter = getchar()) != '\n'; input_index++){

        user_input[input_index] = letter;
    }
    //Fill rest of user_input buffer with terminator to prevent undefined behavior
    while(input_index < 50)user_input[input_index++] = '\0';

    //Parse User input -> interpret numbers
    char *token_in = strtok(user_input, delimiter); 
    
    for(int i = 0; token_in != NULL; i++){

        requested_index[i] = strtol(token_in, NULL, 10);

        token_in = strtok(NULL, delimiter);
    } 

    //Output Requested Buckets
    for(int x = 0; requested_index[x] != -1; x++){
    
        int i = requested_index[x];

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
