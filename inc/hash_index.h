#ifndef hash_index_h
#define hash_index_h
/**
 *Generates hashindex depending on word
 * Formular: `hash_index = word[i] * k ^ i `
 * @param[in] word Assigned Word per Node
 * @param[in] hash_limit size of hashmap array
 * @parma[out] hash_index resulting hashindex between 0 - hashlimit
 */
int hash_index(char *word, int hash_limit);
#endif
