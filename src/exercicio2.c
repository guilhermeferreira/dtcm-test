#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "quicksort.h"

#define ARRAY_COUNT( a ) ( sizeof(a) / sizeof(a[0]) )
#define ARRAY_MAX_ITEMS 32000

/*
 * @brief Initialize each element of the array.
 */
static void init_array(
    int array[],
    int array_count
)
{
    int i;

    assert( ( 0 < array_count ) && ( array_count < ARRAY_MAX_ITEMS ) );

    for ( i = 0; i < array_count; i++ ) {
        array[ i ] = i;
    }
}

/*
 * @brief Sort the array with the greater number first.
 */
static void inverse_sort_array(
    int array[],
    int array_count
)
{
    int first_index;
    int last_index;

    assert( ( 0 < array_count ) && ( array_count < ARRAY_MAX_ITEMS ) );

    first_index = 0;
    last_index = array_count - 1;

    inverse_quicksort( array, first_index, last_index );
}

/*
 * @brief Prints the value of each array item.
 */
static void print_array(
    int array[],
    int array_count
)
{
    int i;

    assert( ( 0 < array_count ) && ( array_count < ARRAY_MAX_ITEMS ) );

    for ( i = 0; i < array_count; i++ ) {
        printf( "%d ", array[ i ] );
    }

    printf( "\n" );
}

int main()
{
    int numbers[ 15 ];
    int first_index;
    int last_index;

    memset( numbers, 0, sizeof(numbers) );

    first_index = 0;
    last_index = (int) ARRAY_COUNT( numbers ) - 1;

    init_array( numbers, (int) ARRAY_COUNT( numbers ) );
    assert( numbers[ first_index ] == first_index );
    assert( numbers[ last_index ] == last_index );
    print_array( numbers, (int) ARRAY_COUNT( numbers ) );

    inverse_sort_array( numbers, (int) ARRAY_COUNT( numbers ) );
    assert( numbers[ first_index ] == last_index );
    assert( numbers[ last_index ] == first_index );
    print_array( numbers, (int) ARRAY_COUNT( numbers ) );

    return 0;
}
