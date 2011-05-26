/*
 * Linked list functions to manipulate the internal list.
 */
#include "linkedlist.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * Head of the list, point to the first NODE_T
 */
static NODE_T *head;


NODE_T *node_alloc( void )
{
    NODE_T *new_node;

    new_node = (NODE_T *) malloc( sizeof(NODE_T) );
    if ( new_node == NULL ) {
        printf( "Failed to alloc NODE_T.\n" );
        return NULL;
    }

    memset( new_node, 0, sizeof(NODE_T) );

    return new_node;
}


void node_free( NODE_T **node )
{
    assert( node != NULL );
    assert( *node != NULL );

    free( *node );
    *node = NULL;
}


/*
 * @brief Initialize the NODE_T fields.
 */
void node_init(
    /*@out@*/NODE_T *node,
    int indicator,
    const char *str,
    /*@null@*/NODE_T *next
)
{
    assert( node != NULL );
    assert( str != NULL );

    node->indicator = indicator;
    strncpy( node->str, str, STR_SIZE );
    node->str[ STR_SIZE ] = '\0';
    node->next = next;
}


/*
 * @brief Insert in the the list the NODE_T passed by argument.
 */
void list_add( const NODE_T *element_to_add )
{
    NODE_T *new_head;

    assert( element_to_add != NULL );

    if ( head == NULL ) {
        /* the list head is not a valid pointer until now */
        head = node_alloc();

        /* copy the fields, except the next, which we handle internally */
        node_init(
                head,
                element_to_add->indicator,
                element_to_add->str,
                NULL
        );
    }
    else {
        new_head = node_alloc();

        /* copy the fields, and insert the new node on top of head */
        node_init(
                new_head,
                element_to_add->indicator,
                element_to_add->str,
                head
        );

        /* insert the new node in the head of the list */
        head = new_head;
    }
}


/*
 * @brief Remove from the list the NODE_T passed by argument.
 */
void list_del( const NODE_T *element_to_del )
{
    NODE_T *previous_node;
    NODE_T *current_node;

    assert( element_to_del != NULL );

    previous_node = NULL;
    current_node = head;
    while ( current_node != NULL ) {
        /* found, in the list, the NODE_T to delete */
        if ( current_node->indicator == element_to_del->indicator ) {

            if ( previous_node != NULL ) {
                previous_node->next = current_node->next;
            }

            node_free( &current_node );

            break;
        }

        previous_node = current_node;
        current_node = current_node->next;
    }
}


/*
 * @brief Search in the list for the NODE_T passed by argument, and return a
 * copy of the found NODE_T, or NULL otherwise.
 */
NODE_T *list_search( const NODE_T *element_to_search )
{
    NODE_T *found_node;
    NODE_T *current_node;

    assert( element_to_search != NULL );

    /* search the NODE_T */
    found_node = NULL;
    current_node = head;
    while ( current_node != NULL ) {
        /* found the NODE_T in the list */
        if ( current_node->indicator == element_to_search->indicator ) {
            found_node = node_alloc();
            node_init(
                    found_node,
                    current_node->indicator,
                    current_node->str,
                    NULL
            );
            break;
        }

        current_node = current_node->next;
    }

    return found_node;
}

