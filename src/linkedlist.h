#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define STR_SIZE 20

typedef struct node
{
    int indicator;
    char str[ STR_SIZE + 1 ];
    struct node *next;
} NODE_T;

NODE_T *node_alloc( void );
void node_free( NODE_T **node );
void node_init(
    /*@out@*/NODE_T *node,
    int indicator,
    const char *str,
    /*@null@*/NODE_T *next
);

void list_add( const NODE_T *element_to_add );
void list_del( const NODE_T *element_to_del );
NODE_T *list_seach( const NODE_T *element_to_search );


#endif /* LINKEDLIST_H */
