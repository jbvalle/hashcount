#ifndef CENSOR_BUCKETS_H
#define CENSOR_BUCKETS_H


void remove_key_word(char *input_string, char *comparison_string);

void censor_buckets(node_t **buckets, FILE *input_stream, FILE *output_stream, int *requested_index);

#endif
