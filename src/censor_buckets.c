/**
 *@file censor_buckets.c
 *@author John Bryan Valle
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"
#define COLOR "\033[0;93m"
#define RESET "\033[0m"


/**
 *@brief Removes keywords of buckets from a string.<br />
 *A string is itteratively analyzed and letterwise compared with the keyword
 *if a complete Keyword was matched remove by rplacing characters with dashes
 *@param[in] input_string current line
 *@param[in] comparison_string String of a Bucket element
 */
void remove_key_word(char *input_string, char *comparison_string){


    int input_string_len = strlen(input_string);
    int comparison_string_len = strlen(comparison_string);

    int x;

    for(int i = 0; i <= (input_string_len - (int)strlen(comparison_string)); i++){

        ///1. Check for match
        for(x = 0; x < comparison_string_len; x++){

           if(comparison_string[x] != input_string[i + x])break;
        }
        ///2. If match found increment occurance and delete word
        if(x == comparison_string_len){

            for(int k = i; k < i + comparison_string_len;k++){
                ///3. Replace matching keyword character
                input_string[k] = '-';
            }
            ///4. Set current index to end of word
            i += comparison_string_len - 1;
        }
    }
}

/**
 *@brief Itterate through all lines and check for all words in buckets.<br />
 *@param[in] buckets All buckets of given requested indices are checed
 *@param[in] input_stream Current Input stream of an input text 
 *@param[in] output_stream Output Stream to write new line 
 *@param[in] requested_index Array with all requested indices
 */
void censor_buckets(node_t **buckets, FILE *input_stream, FILE *output_stream, int *requested_index){

    //Output Requested Buckets
    char buff[100];

    while(fgets(buff,sizeof(buff),input_stream)!=NULL){

        //===================================
        ///1. request word of single bucket
        //===================================
        for(int x = 0; requested_index[x] != -1; x++){
        
            int i = requested_index[x];

            node_t *ptr = buckets[i];
            
            for(int j = 1; ptr != NULL; ptr = ptr->next, j++){
                
                //======================================
                ///2. remove words inside bucket from string
                //======================================
                remove_key_word(buff, ptr->word);
            }
        }
        fputs(buff, output_stream);
        for(int i = 0; i < 100; i++)buff[i]='\0';
    }

}


