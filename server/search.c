#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "search.h"


void read_data(words_st* words, const char * s){
    FILE * fp = fopen(s, "r");
    if(fp == 0x0){
        printf("cannot open %s\n", s);
    } 
    int cap=5;
    int size=0;
    words->words = (trie **)malloc(sizeof(trie *)*cap);
    while(1){
        char buf[1024];
        if(fgets(buf, 1023, fp) == 0x0)
            break;
        int len = strlen(buf);
        buf[len-1] = '\0';
        len--;
        char * count_c = 0x0;
        for(int i = len-1; i >= 0; i--){
            if(buf[i] == ' '){
                buf[i] = '\0';
                count_c = &buf[i+1];
                break;
            }
        }
        int count = atoi(count_c);
        words->words[size++] = make_trie(buf, count);
        if(size >= cap){
            cap*=2;
            words->words = (trie **)realloc(words->words, sizeof(trie *)*cap);
        }
    }
    words->cap = cap;
    words->size = size;
}

words_st * search_word(const words_st * words, const char * s){
    words_st * searchw = (words_st *)malloc(sizeof(words_st));
    int size = 0;
    int cap = 5;
    searchw->words = (trie **)malloc(sizeof(trie *)*cap);
    for(int i = 0; i < words->size; i++){
        if(words->words[i]->search(words->words[i], s) == 0x0)
            continue;
        searchw->words[size++] = words->words[i];
        if(size >= cap){
            cap *= 2;
            searchw->words = (trie **)realloc(words->words, sizeof(trie *)*cap);
        }
    }
    searchw->size = size;
    searchw->cap = cap;
    return searchw;
}

void swap(trie* a, trie* b) 
{ 
    trie temp = *a; 
    *a = *b;
    *b = temp;
} 

int partition(trie ** arr, int low, int high) 
{ 

    int pivot = arr[low]->count; 
    int i = low; 
    int j = high;

    while (i < j) {

        while (arr[i]->count > pivot && i <= high - 1) { 
            i++; 
        } 

        while (arr[j]->count <= pivot && j >= low + 1) {
            j--; 
        }
        if (i < j) {
            swap(arr[i], arr[j]);
        } 
    } 
    swap(arr[low], arr[j]); 
    return j; 
} 

void quickSort(trie ** arr, int low, int high) 
{ 
    if (low < high) { 

        int partitionIndex = partition(arr, low, high); 

        quickSort(arr, low, partitionIndex - 1); 
        quickSort(arr, partitionIndex + 1, high); 
    } 
}
void sort_word(words_st * words){
    quickSort(words->words, 0, words->size-1);
}
char ** trie_to_str(const words_st * words){
    char ** strs = (char **)malloc(sizeof(char *)*10);
    for(int i = 0; i < words->size; i++){
        if(i >= 10)break;
        strs[i] = words->words[i]->word;
    }
    return strs;
}
