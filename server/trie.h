#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "list.h"
#define MAX_CHAR 256

typedef struct _trie_node{
    struct _trie_node * children[MAX_CHAR];
    list * indexes;
    void (* insert)(struct _trie_node * root, const char * s, int index);
    list * (* search_node)(struct _trie_node * root, const char * s);
} trie_node;

typedef struct _trie{
    trie_node * root;
    list * (* search)(struct _trie * t, const char * s);
    int count;
    char * word;
}trie;

void insert(trie_node * root, const char * s, int index);

list * search(trie * t, const char * s);

list * search_node(trie_node * root, const char * s);

trie_node * make_node();

trie * make_trie(const char * s, int count);

