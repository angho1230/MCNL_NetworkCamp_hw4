#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "list.h"

void push_back(list *l, int x){
    if(l->size >= l->capacity){
        l->capacity *= 2;
        l->data = (int *)realloc(l->data, l->capacity * sizeof(int));
    }
    l->data[l->size++] = x;
}
void clear(list *l){
    l->size = 0;
}
int front(list *l){
    return l->data[0];
}
int back(list *l){
    return l->data[l->size - 1];
}
list * make_list(){
    list *l = (list *)malloc(sizeof(list));
    l->size = 0;
    l->capacity = 5;
    l->data = (int *)malloc(l->capacity * sizeof(int));
    l->push_back = push_back;
    l->clear = clear;
    l->front = front;
    l->back = back;
    return l;
}
