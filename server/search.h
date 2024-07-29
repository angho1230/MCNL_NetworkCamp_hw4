#include "trie.h"

typedef struct _words_st{
    trie ** words;
    int size;
    int cap;
}words_st;
    
void read_data(words_st* words, const char * s);
words_st * search_word(const words_st * words, const char * s);
void sort_word(words_st * words);
char ** trie_to_str(const words_st * words);
