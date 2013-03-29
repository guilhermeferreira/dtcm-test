/*
 * Modified version of Insertion-sort algorithm.
 * Reference from Intropduction to Algorithms, 3rd edition
 */
#include "sort.h"

/*
 * @brief Performs an inverse Insertion-sort.
 */
void inverse_sort(
    int array[],
    /*@unused@*/ int left_index,
    int right_index
)
{
    int j;
    int i;
    int key;

    for ( j = 1; j <= right_index; j++ ) {
        key = array[j];
        i = j - 1;

        while ( (i >= 0) && (array[i] < key) ) {
            array[i + 1] = array[i];
            i = i - 1;
        }
        array[i + 1] = key;
    }
}

