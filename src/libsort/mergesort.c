/*
 * Modified version of Merge-sort algorithm.
 * Reference from Introduction to Algorithms, 3rd edition
 */
#include "sort.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

/*
 * @brief Merge
 */
static void merge(
    int array[],
    int left_index,
    int middle_index,
    int right_index
)
{
    int n1 = middle_index - left_index + 1;
    int n2 = right_index - middle_index;
    int *array_left = NULL;
    int *array_right = NULL;
    int i = 0;
    int j = 0;
    int k = 0;

    assert( middle_index >= left_index );
    assert( right_index > middle_index );

    array_left = calloc( (size_t) n1 + 1, sizeof(int) );
    if ( array_left == NULL ) {
        exit( EXIT_FAILURE );
    }
    array_right = calloc( (size_t) n2 + 1, sizeof(int) );
    if ( array_right == NULL ) {
        exit( EXIT_FAILURE );
    }

    /* copy the elements at left to L array */
    for ( i = 0; i < n1; i++ ) {
        array_left[ i ] = array[ left_index + i ];
    }

    /* copy the elements at right to R array */
    for ( j = 0; j < n2; j++ ) {
        array_right[ j ] = array[ middle_index + j + 1 ];
    }

    array_left[ n1 ] = -1;
    array_right[ n2 ] = -1;

    i = 0;
    j = 0;

    /* combine the two arrays (left and right), placing in A array the greatest
       elements */
    for ( k = left_index; k <= right_index; k++ ) {
        if ( array_left[ i ] > array_right[ j ] ) {
            array[ k ] = array_left[ i ];
            i++;
        }
        else {
            array[ k ] = array_right[ j ];
            j++;
        }
    }

    free( array_left );
    free( array_right );
}

/*
 * @brief Performs an inverse Merge-sort.
 */
void inverse_sort(
    int array[],
    int left_index,
    int right_index
)
{
    int middle_index = 0;

    if ( left_index < right_index ) {
        middle_index = (int) floor( ( left_index + right_index ) / 2.0 );

        inverse_sort( array, left_index, middle_index );
        inverse_sort( array, middle_index + 1, right_index );

        merge( array, left_index, middle_index, right_index );
    }
}
