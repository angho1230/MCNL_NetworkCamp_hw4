#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_CHAR 256

// A Suffix Trie (A Trie of all suffixes) Node
/*
class SuffixTrieNode
{
private:
    SuffixTrieNode *children[MAX_CHAR];
    list<int> *indexes;
public:
    SuffixTrieNode() // Constructor
    {
        // Create an empty linked list for indexes of
        // suffixes starting from this node
        indexes = new list<int>;
 
        // Initialize all child pointers as NULL
        for (int i = 0; i < MAX_CHAR; i++)
          children[i] = NULL;
    }
 
    // A recursive function to insert a suffix of the txt
    // in subtree rooted with this node
    void insertSuffix(string suffix, int index);
 
    // A function to search a pattern in subtree rooted
    // with this node.The function returns pointer to a linked
    // list containing all indexes where pattern is present.
    // The returned indexes are indexes of last characters
    // of matched text.
    list<int>* search(string pat);
};
*/

typedef struct _list{
    int size;
    int capacity;
    int *data;
    struct _list * (*make_list)();
    void (* push_back)(struct _list *, int);
    void (* clear)(struct _list *);
    int (* front)(struct _list *);
    int (* back)(struct _list *);
}list;

typedef struct _trie_node{
    struct _trie_node * children[MAX_CHAR];
    list * indexes;
    //struct _trie_node * (* make_node)(void);
    void (* insert)(struct _trie_node * root, const char * s, int index);
    list * (* search_node)(struct _trie_node * root, const char * s);
} trie_node;

typedef struct _trie{
    trie_node * root;
    //struct _trie * (* make_trie)(const char * s);
    void (* search)(struct _trie * t, const char * s);
}trie;

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

trie_node * make_node();
/*
void SuffixTrieNode::insertSuffix(string s, int index)
{
    // Store index in linked list
    indexes->push_back(index);
 
    // If string has more characters
    if (s.length() > 0)
    {
        // Find the first character
        char cIndex = s.at(0);
 
        // If there is no edge for this character, add a new edge
        if (children[cIndex] == NULL)
            children[cIndex] = new SuffixTrieNode();
 
        // Recur for next suffix
        children[cIndex]->insertSuffix(s.substr(1), index+1);
    }
}
*/
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

void search(trie * t, const char * s){
    list * result = t->root->search_node(t->root, s);

    if(result == 0x0){
        printf("Pattern not found\n");
    }else{
        int patLen = strlen(s);
        for(int i = 0; i < result->size; i++){
            printf("Pattern found at position %d\n", result->data[i] - patLen);
        }
    }
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

trie * make_trie(const char * s){
    trie *t = (trie *)malloc(sizeof(trie));
    t->root = make_node();
    t->search = search;
    int len = 0;
    while(*(s+len) != '\0'){
        t->root->insert(t->root, s+len, len);
        len++;
    }
    return t;
}



/*
// A recursive function to search a pattern in subtree rooted with
// this node
list<int>* SuffixTrieNode::search(string s)
{
    // If all characters of pattern have been processed,
    if (s.length() == 0)
        return indexes;
 
    // if there is an edge from the current node of suffix trie,
    // follow the edge.
    if (children[s.at(0)] != NULL)
        return (children[s.at(0)])->search(s.substr(1));
 
    // If there is no edge, pattern doesn’t exist in text
    else return NULL;
}

y void SuffixTrie::search(string pat)
{
    // Let us call recursive search function for root of Trie.
    // We get a list of all indexes (where pat is present in text) in
    // variable 'result'
    list<int> *result = root.search(pat);
 
    // Check if the list of indexes is empty or not
    if (result == NULL)
        cout << "Pattern not found" << endl;
    else
    {
       list<int>::iterator i;
       int patLen = pat.length();
       for (i = result->begin(); i != result->end(); ++i)
         cout << "Pattern found at position " << *i - patLen<< endl;
    }
}
 
// driver program to test above functions
*/
int main()
{
    // Let us build a suffix trie for text "geeksforgeeks.org"
    //string txt = "CAFE Pohang Handong";
    //SuffixTrie S(txt);
    char txt[] = "CAFE Pohang Handong";
    char ftxt[] = "Pohang";
    trie * t = make_trie(txt);
    t->search(t, ftxt);
    return 0;
}
