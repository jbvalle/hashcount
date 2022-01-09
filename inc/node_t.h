#ifndef NODE_T_H
#define NODE_T_H
/**
 * `node_t` linked list bucket element with 
 *  word elements
 */
typedef struct node{

    char word[15];
    int occurance;
    struct node *next;
}node_t;
#endif
