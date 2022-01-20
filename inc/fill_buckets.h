#ifndef FILL_BUCKETS_H
#define FILL_BUCKETS_H
/**
 *Adds new node to list using stack(), insert() and append() function
 *Add new node in alphabetical order depending in string members of elements
 *@param[in] head headreference of list
 *@param[in] new_key new string member of new node
 */


uint64_t pow_t(int base, int exp);

int hash_index(char *word, int hash_limit);

void add_node(node_t **head, char *new_key);

void fill_buckets(node_t **buckets, int hash_limit, FILE *input_stream);
#endif
