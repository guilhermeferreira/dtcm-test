#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

int main()
{
    NODE_T node_a; /* arbitrary nodes, better name then a, b, c? */
    NODE_T node_b;
    NODE_T node_c;
    NODE_T *node_found;

    node_init( &node_a, 1, "Primeiro", NULL );
    node_init( &node_b, 3, "Terceiro", NULL );
    node_init( &node_c, 7, "Setimo", NULL );

    node_found = list_seach( &node_a );
    assert( node_found == NULL );
    node_found = list_seach( &node_b );
    assert( node_found == NULL );
    node_found = list_seach( &node_c );
    assert( node_found == NULL );

    list_add( &node_a );
    node_found = list_seach( &node_a );
    assert( node_found != NULL );
    free( node_found );
    node_found = list_seach( &node_b );
    assert( node_found == NULL );
    node_found = list_seach( &node_c );
    assert( node_found == NULL );

    list_add( &node_b );
    node_found = list_seach( &node_a );
    assert( node_found != NULL );
    free( node_found );
    node_found = list_seach( &node_b );
    assert( node_found != NULL );
    free( node_found );
    node_found = list_seach( &node_c );
    assert( node_found == NULL );

    list_add( &node_c );
    node_found = list_seach( &node_a );
    assert( node_found != NULL );
    free( node_found );
    node_found = list_seach( &node_b );
    assert( node_found != NULL );
    free( node_found );
    node_found = list_seach( &node_c );
    assert( node_found != NULL );
    free( node_found );

    node_found = list_seach( &node_a );
    assert( node_found->indicator == node_a.indicator );
    free( node_found );
    node_found = list_seach( &node_b );
    assert( node_found->indicator == node_b.indicator );
    free( node_found );
    node_found = list_seach( &node_c );
    assert( node_found->indicator == node_c.indicator );
    free( node_found );

    return 0;
}
