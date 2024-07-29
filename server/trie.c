#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "trie.h"
#define MAX_CHAR 256

void insert(trie_node * root, const char * s, int index){
    root->indexes->push_back(root->indexes, index);

    if(s[0] != '\0'){
        char cIndex = s[0];

        if(root->children[cIndex] == 0x0){
            root->children[cIndex] = make_node();
        }
        root->children[cIndex]->insert(root->children[cIndex], s+1, index+1);
    }
}

list * search(trie * t, const char * s){
    list * result = t->root->search_node(t->root, s);
    return result;
}
list * search_node(trie_node * root, const char * s){
    if(s[0] == '\0'){
        return root->indexes;
    }
    if(root->children[s[0]] != 0x0){
        return root->children[s[0]]->search_node(root->children[s[0]], s+1);
    }
    return 0x0;
}

trie_node * make_node(){
    trie_node * n = (trie_node *)malloc(sizeof(trie_node));
    n->indexes = make_list();
    n->insert = insert;
    n->search_node = search_node;
    return n;
}

trie * make_trie(const char * s, int count){
    trie *t = (trie *)malloc(sizeof(trie));
    t->root = make_node();
    t->search = search;
    t->count = count;
    t->word = strdup(s);
    int len = 0;
    while(*(s+len) != '\0'){
        t->root->insert(t->root, s+len, len);
        len++;
    }
    return t;
}

