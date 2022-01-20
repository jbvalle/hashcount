/**
 *@file main.c
 * `main.c` main entry point for hashcount program
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "../inc/node_t.h"
#include "../inc/free_buckets.h"
#include "../inc/stack.h"
#include "../inc/append.h"
#include "../inc/insert.h"
#include "../inc/fill_buckets.h"
#include "../inc/censor_except_buckets.h"
#include "../inc/censor_buckets.h"
#include "../inc/choose_buckets.h"
#include "../inc/display_list.h"

#define COLOR "\033[0;94m"
#define RESET "\033[0m"


int main(int argc, char **argv){
    
    //Set Maximum hashlimit
    const int hash_limit = 40;

    node_t *buckets[40];

    for(int i = 0; i < hash_limit; i++)buckets[i] = NULL;

    //=================================================
    // Fetch User input arguments for removing or
    // censoring text
    // ================================================

    int chosen_flag[2] = {0, 0};
    int option;

    char input_file[100];

    while((option = getopt(argc, argv, "f:rc")) != -1){

        if(option == 'f')strcpy(input_file, optarg);
        if(option == 'r')chosen_flag[0] = 1;
        if(option == 'c')chosen_flag[1] = 1;
    }
    
    if(argc <= 1){
        
        printf("\nDefault Input file file_streams/default.txt used\n");
        strcpy(input_file, "file_streams/default.txt");
    }
    //=================================================
    // infuse buckets with input words
    //=================================================

    FILE *input_stream_censored;
    FILE *input_stream = fopen(input_file, "r");
    FILE *output_stream = fopen("file_streams/buckets.txt", "wb+");

    fill_buckets(buckets, hash_limit, input_stream);
    
    display_list(buckets, output_stream, 40);

    //Close input and output streams
    fclose(input_stream);input_stream = NULL;
    fclose(output_stream);output_stream = NULL;

    //=================================================
    // Select buckets and output new textfile
    //=================================================

    //Initilize array for requested indices
    int requested_index[50];
    int requested_index_size = (int)sizeof(requested_index)/(int)sizeof(requested_index[0]);
    //Initialize requestedindex with -1
    for(int i = 0; i < requested_index_size; i++)requested_index[i] = -1;

    
    //=================================================
    // remove requested buckets from textfile 
    // and write to new textfile
    // ================================================
    if(chosen_flag[0]){

        input_stream  = fopen(input_file, "r");
        output_stream = fopen("file_streams/censored_buckets.txt", "wb+");
        
        //Request user input
        choose_buckets(buckets, requested_index, chosen_flag);
        //Censor all words matching chosen buckets
        //and write to censored_buckets.txt
        censor_buckets(buckets, input_stream, output_stream, requested_index);

        //Close input and output streams
        fclose(input_stream);input_stream = NULL;
        fclose(output_stream);output_stream = NULL;
    }
    //=================================================
    // remove everything except buckets from textfile
    // and write to new textfile
    // ===============================================
    if(chosen_flag[1]){

        // Reinit array for requested indices
        for(int i = 0; i < requested_index_size; i++)requested_index[i] = -1;

        input_stream          = fopen(input_file, "r");
        output_stream = fopen("file_streams/temp.txt", "wb+");

        //Request user input
        choose_buckets(buckets, requested_index, chosen_flag);
        //Censor all word matching the buckets
        censor_buckets(buckets, input_stream, output_stream, requested_index);

        //Close input and output streams
        fclose(input_stream);input_stream = NULL;
        fclose(output_stream);output_stream = NULL;

        input_stream          = fopen(input_file, "r");
        input_stream_censored = fopen("file_streams/temp.txt", "r");
        output_stream         = fopen("file_streams/censored_all_except_buckets.txt", "wb+");
        
        //Read censored textfile and compare to original input file and replace all letter with censored char
        //Write new file to censored_all_except_buckets.txt
        censor_except_buckets(input_stream, input_stream_censored, output_stream);

        fclose(input_stream_censored);input_stream_censored = NULL;
        fclose(input_stream);input_stream = NULL;
        fclose(output_stream);output_stream = NULL;
    }
    //=================================================
    // free all nodes
    //=================================================
    for(int i = 0; i < hash_limit; i++)free_buckets(buckets[i]);

    return 0;
}


