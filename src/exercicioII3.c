#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE         50
#define ARRAY_COUNT( a )    ( sizeof(a) / sizeof(a[0]) )

#ifdef __UGLY_FORMAT_OUTPUT__
static void FormatOutput( char * String )
{
    int x, c, d, i;
    char Work[ 20 ];

    x = strlen( String ) - 1;

    for ( i = 1, c = x + (x / 3) + 1, d = x; c > 0; --c, --d, ++i ) {
        if ( i % 4 == 0 ) {
            *(Work + (--c)) = ',';
            i = 1;
        }
        *(Work + (c - 1)) = *(String + d);
    }

    Work[ x + (x / 3) + 1 ] = '\0';

    strcpy( String, Work );
}
#else
static void FormatOutput( const char *input, /*@out@*/char *output )
{
    size_t input_size;
    size_t work_size;
    size_t comma_count; /* numero de virgulas */
    int three_char_count; /* controle para cada 3 caracteres */
    int input_index;
    int work_index;
    char *work; /* nao possui o limite de 20 caracteres do codigo antigo */

    assert( input != NULL );
    assert( output != NULL );

    input_size = strlen( input );

    comma_count = input_size / 3;
    work_size = input_size + comma_count;
    work = malloc( work_size + 1 );
    if ( work == NULL ) {
        printf( "Could not allocate work memory\n" );
        return;
    }
    memset( work, 0xFF, work_size );

    three_char_count = 1;
    input_index = (int) input_size - 1;
    work_index = (int) work_size - 1;
    while ( 0 <= work_index ) {
        /* adiciona uma virgula a cada 3 caracteres */
        if ( ( three_char_count % 4 ) == 0 ) {
            work[ work_index ] = ',';
            --work_index;
            three_char_count = 1;
        }

        work[ work_index ] = input[ input_index ];

        ++three_char_count;
        --input_index;
        --work_index;
    }
    work[ work_size ] = '\0';

    strncpy( output, work, work_size );

    free( work );
}
#endif

int main( int argc, char *argv[ ] )
{
    char input[ BUFFER_SIZE ];
    char output[ BUFFER_SIZE ];

    if ( argc < 2 ) {
        printf( "Need pass argument\n" );
        return -1;
    }

    memset( output, 0, ARRAY_COUNT( output ) );
    FormatOutput( argv[ 1 ], output );
    printf( "String format output=[ %s ]\n", output );

    strncpy( input, "Abcde", ARRAY_COUNT( input ) );
    memset( output, 0, ARRAY_COUNT( output ) );
    FormatOutput( input, output );
    assert( strncmp( output, "Ab,cde", ARRAY_COUNT( output ) ) == 0 );

    strncpy( input, "1234567890", ARRAY_COUNT( input ) );
    memset( output, 0, ARRAY_COUNT( output ) );
    FormatOutput( input, output );
    assert( strncmp( output, "1,234,567,890", ARRAY_COUNT( output ) ) == 0 );

    return 0;
}
