#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"
#define COLOR "\033[0;94m"
#define RESET "\033[0m"



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


