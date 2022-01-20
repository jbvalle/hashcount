#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../inc/node_t.h"
#include "../inc/free_buckets.h"
#include "../inc/stack.h"
#include "../inc/append.h"
#include "../inc/insert.h"
#include "../inc/fill_buckets.h"


#define COLOR "\033[0;94m"
#define RESET "\033[0m"


void censor_except_buckets(FILE *input_stream, FILE *input_stream_censored, FILE *output_stream){

    //Output Requested Buckets
    char buff_input1[100];
    char buff_input2[100];

    while((fgets(buff_input1,sizeof(buff_input1),input_stream))&&(fgets(buff_input2,sizeof(buff_input2),input_stream_censored)!=NULL)){

        for(int x = 0; x < (int)strlen(buff_input1); x++){
        
            if(buff_input2[x] != '-')buff_input1[x] = '-';

        }
        fputs("\n", output_stream);
        fputs(buff_input1, output_stream);
        //fprintf(output_stream, "\n");
        for(int i = 0; i < 100; i++)buff_input1[i]='\0';
        for(int i = 0; i < 100; i++)buff_input2[i]='\0';
    }

}
