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

void remove_key_word(char *input_string, char *comparison_string){


    int input_string_len = strlen(input_string);
    int comparison_string_len = strlen(comparison_string);

    int x;

    for(int i = 0; i <= (input_string_len - (int)strlen(comparison_string)); i++){

        //Check for match
        for(x = 0; x < comparison_string_len; x++){

           if(comparison_string[x] != input_string[i + x])break;
        }
        //If match found increment occurance and delete word
        if(x == comparison_string_len){

            for(int k = i; k < i + comparison_string_len;k++){
                
                input_string[k] = '-';
            }
            //set current index to end of word
            i += comparison_string_len - 1;
        }
    }
}

void censor_buckets(node_t **buckets, FILE *input_stream, FILE *output_stream, int *requested_index){

    //Output Requested Buckets
    char buff[100];

    while(fgets(buff,sizeof(buff),input_stream)!=NULL){

        //===================================
        //request word of single bucket
        //===================================
        for(int x = 0; requested_index[x] != -1; x++){
        
            int i = requested_index[x];

            node_t *ptr = buckets[i];
            
            for(int j = 1; ptr != NULL; ptr = ptr->next, j++){
                
                //======================================
                //remove words inside bucket from string
                //======================================
                remove_key_word(buff, ptr->word);
            }
        }
        fputs(buff, output_stream);
        //fprintf(output_stream, "\n");
        for(int i = 0; i < 100; i++)buff[i]='\0';
    }
}

void censor_except_buckets(FILE *input_stream, FILE *input_stream_censored, FILE *output_stream){

    //Output Requested Buckets
    char buff_input1[100];
    char buff_input2[100];

    while((fgets(buff_input1,sizeof(buff_input1),input_stream))&&(fgets(buff_input2,sizeof(buff_input2),input_stream_censored)!=NULL)){

        for(int x = 0; x < (int)strlen(buff_input1); x++){
        
            if(buff_input2[x] != '-')buff_input1[x] = '-';

        }
        fputs(buff_input1, output_stream);
        //fprintf(output_stream, "\n");
        for(int i = 0; i < 100; i++)buff_input1[i]='\0';
        for(int i = 0; i < 100; i++)buff_input2[i]='\0';
    }
}
void fill_buckets(node_t **buckets, int hash_limit, FILE *input_stream){


    char buff[100];
    char *token;char delimiter[] = " .\n;:,?\t";

    while(fgets(buff,sizeof(buff),input_stream)!=NULL){

        token = strtok(buff, delimiter);
        
        while(token!=NULL){
            
            add_node(&buckets[hash_index(token, hash_limit)], token);
            
            token = strtok(NULL, delimiter);
        } 
        printf("\n");
        
        for(int i = 0; i < 100; i++)buff[i]='\0';
    }


}

void choose_buckets(node_t **buckets, int *requested_index){


    char delimiter[] = " .\n;:,?\t";
    char user_input[50], letter;
    int input_index;
    //Initialize user_input
    for(int i = 0; i < 50; i++)user_input[i] = '\0';
    

    printf("\n+-----------------------------------------+\n");
    printf("| Please enter desired indices of buckets |\n");
    printf("+-----------------------------------------+\n");
    printf("\n»");
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

int main(int argc, char **argv){
    
    ///1. Init `buckets` array of nodes
    int hash_limit = 40;
    node_t *buckets[40];

    for(int i = 0; i < hash_limit; i++)buckets[i] = NULL;

    //=================================================
    // infuse buckets with input words
    //=================================================

    FILE *input_stream = fopen("file_streams/input.txt", "r");
    FILE *output_stream = fopen("file_streams/buckets.txt", "wb+");

    fill_buckets(buckets, hash_limit, input_stream);
    
    display_list(buckets, output_stream, 40);

    //Close input and output streams
    fclose(input_stream);input_stream = NULL;
    fclose(output_stream);output_stream = NULL;

    //=================================================
    // Select buckets and output new textfile
    //=================================================

    int requested_index[50];

    int requested_index_size = (int)sizeof(requested_index)/(int)sizeof(requested_index[0]);
    //Initialize requestedindex
    for(int i = 0; i < requested_index_size; i++)requested_index[i] = -1;

    choose_buckets(buckets, requested_index);
    
    //=================================================
    // remove requested buckets from textfile 
    // and write to new textfile
    // ================================================
    input_stream = fopen("file_streams/input.txt", "r");
    output_stream = fopen("file_streams/censored_buckets.txt", "wb+");
    

    censor_buckets(buckets, input_stream, output_stream, requested_index);

    //Close input and output streams
    fclose(input_stream);input_stream = NULL;
    fclose(output_stream);output_stream = NULL;


    //=================================================
    // remove everything except buckets from textfile
    // and write to new textfile
    // ===============================================
    FILE *input_stream_censored = fopen("file_streams/censored_buckets.txt", "r");
    input_stream = fopen("file_streams/input.txt", "r");
    output_stream = fopen("file_streams/censored_all_except_buckets.txt", "wb+");
    
    censor_except_buckets(input_stream, input_stream_censored, output_stream);

    fclose(input_stream_censored);input_stream_censored = NULL;
    fclose(input_stream);input_stream = NULL;
    fclose(output_stream);output_stream = NULL;
    //=================================================
    // free all nodes
    //=================================================
    for(int i = 0; i < hash_limit; i++)free_buckets(buckets[i]);

    return 0;
}


