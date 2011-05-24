#include <assert.h>

static int max(
    int first,
    int second
)
{
    if ( first > second ) {
        return first;
    }
    else {
        return second;
    }
}

static int max3(
    int first,
    int second,
    int third
)
{
    int max_first_second;

    max_first_second = max( first, second );

    return max( third, max_first_second );
}


int main()
{
    int greater_num;

    greater_num = max3( 1, 2, 3 );
    assert( greater_num == 3 );

    greater_num = max3( 3, 2, 1 );
    assert( greater_num == 3 );

    greater_num = max3( 2, 3, 1 );
    assert( greater_num == 3 );

    return 0;
}
