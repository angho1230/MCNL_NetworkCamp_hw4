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


list * make_list();
void push_back(list *l, int x);
void clear(list *l);
int front(list *l);
int back(list *l);
