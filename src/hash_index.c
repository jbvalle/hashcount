#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * `pow_t` serves as an alternative to pow() from math library
 * @param[in] base Base
 * @param[in] exp Power
 * @param[out] result 
 */
uint64_t pow_t(int base, int exp){
    
    ///1. Initialize result variable
    uint64_t result = 1;

    ///2. Catch zero exponent return 1
    if(exp == 0)return 1;

    ///3. Error catch negative exp, in this application neg exp not required
    if(exp < 0)return -1;

    ///4. Multiply base with itself exp times
    for(int i = 0; i < exp; i++){
        result *= (uint64_t)base;
    }

    ///5. Return resulting value
    return result;
}
/**
 *Generates hashindex depending on word
 * Formular: `hash_index = word[i] * k ^ i `
 * @param[in] word Assigned Word per Node
 * @param[in] hash_limit size of hashmap array
 * @parma[out] hash_index resulting hashindex between 0 - hashlimit
 */
int hash_index(char *word, int hash_limit){
    
    ///1. Initialize hash_value variable
    uint64_t hash_value = 0;
    int hash_const = 13;

    ///2. Iterate through letters and perform formular
    for(int i = 0; word[i] != '\0'; i++){

        hash_value += word[i] * pow_t(hash_const, i);
    }

    ///3. Return forumlar
    return hash_value%hash_limit;
}
