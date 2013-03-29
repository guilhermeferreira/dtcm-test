/*
 * Modified version of Quick-sort algorithm.
 * Reference from http://en.wikipedia.org
 */
#include "sort.h"

/*
 * @brief Swap the value of the two array items identified by the indexes.
 */
static void swap_items(
    int array[],
    int item1_index,
    int item2_index
)
{
    int temp_value;

    temp_value = array[ item1_index ];
    array[ item1_index ] = array[ item2_index ];
    array[ item2_index ] = temp_value;
}


/*
 * @brief Performs an inverse partition, moving the elements to the side of
 * pivot.
 */
static int inverse_partition(
    int array[],
    int left_index,
    int right_index,
    int pivot_index
)
{
    int pivot_value;
    int store_index;
    int i;

    pivot_value = array[ pivot_index ];

    /* swap items: move pivot to the end */
    swap_items( array, pivot_index, right_index );

    store_index = left_index;

    for ( i = left_index; i < right_index; i++ ) {
        if ( array[ i ] > pivot_value ) {
            /* swap items: move items greater than pivot to the left of it */
            swap_items( array, i, store_index );

            ++store_index;
        }

    }

    /* swap items: move pivot to its final place */
    swap_items( array, store_index, right_index );

    return store_index;
}

/*
 * @brief Performs an inverse Quick-sort.
 */
void inverse_sort(
    int array[],
    int left_index,
    int right_index
)
{
    int pivot_index;

    if ( right_index > left_index ) {
        /* choose the pivot: median */
        pivot_index = ( right_index + left_index ) / 2;
        pivot_index = inverse_partition(
            array, left_index, right_index, pivot_index
        );
        inverse_sort( array, left_index, pivot_index - 1 );
        inverse_sort( array, pivot_index + 1, right_index );
    }
}
