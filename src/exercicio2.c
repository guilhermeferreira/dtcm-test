#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "sort.h"

#define ARRAY_COUNT( a )                     ( sizeof(a) / sizeof(a[0]) )
#define ARRAY_ITEMS_MAX_COUNT                INT_MAX
#define ARRAY_ITEMS_COUNT                    30

typedef void (*sort_func_ptr_t)(int[], int, int);

/*@null@*/ static void *handle = NULL;


/*
 * @brief Initialize each element of the array.
 */
static void init_array(
    int array[],
    int array_count
)
{
    int i;

    assert( ( 0 < array_count ) && ( array_count < ARRAY_ITEMS_MAX_COUNT ) );

    for ( i = 0; i < array_count; i++ ) {
        array[ i ] = i;
    }
}

/*
 * @brief Load the library with the given sort algorithm.
 * @note Require a export LD_LIBRARY_PATH=./src/.libs/ to know where to find the libraries
 */
static sort_func_ptr_t load_sort_function(
    const char alg_name[],
    const char func_name[]
)
{
    const char lib_prefix[] = "lib";
    const char lib_sufix[] = ".so";
    char *error = NULL;
    char *lib_name = NULL;
    size_t lib_name_size = 0;
    sort_func_ptr_t func_ptr;

    assert( alg_name != NULL );
    assert( func_name != NULL );

    /* Reserve space to build the dynamic library name */
    lib_name_size = sizeof(lib_prefix) + strlen(alg_name) + sizeof(lib_sufix);
    lib_name = malloc( lib_name_size + 1 );
    if ( lib_name == NULL ) {
        fprintf( stderr, "Failed to load library: malloc() failed!\n" );
        exit( EXIT_FAILURE );
    }

    /* Builds the library name lib<algorithm>.so (e.g. libquicksort.so) */
    strcpy( lib_name, lib_prefix );
    strcat( lib_name, alg_name );
    strcat( lib_name, lib_sufix );
    lib_name[ lib_name_size ] = '\0';

    /* Open a handle to the dynamic library */
    printf( "Loading library %s... ", lib_name );
    handle = dlopen( lib_name, RTLD_LAZY );
    if ( handle == (void *)NULL ) {
        fprintf( stderr, "Failed to load the library %s\n", dlerror() );
        exit( EXIT_FAILURE );
    }
    printf("done.\n");

    /* Check access to the sort_func() function */
    printf( "Linking against function %s... ", func_name );
    /* Writing: ptr = (void (*)(int[], int, int)) dlsym(handle, func_name);
       would seem more natural, but the C99 standard leaves casting from
       "void *" to a function pointer undefined.
       The assignment used below is the POSIX.1-2003 (Technical Corrigendum 1)
       workaround; see the Rationale for the POSIX specification of dlsym(). */
    *(void **) (&func_ptr) = dlsym( handle, func_name );
    error = dlerror();
    if ( error != NULL ) {
        fprintf( stderr, "Failed to load the library %s\n", error );
        exit( EXIT_FAILURE );
    }
    printf("done.\n");

    assert( lib_name_size > 0 );
    assert( lib_name != NULL );
    assert( func_ptr != NULL );

    free( lib_name );

    return func_ptr;
}

/*
 * @brief Load the library with the given sort algorithm.
 * @note You cannot use any function from the library after close the handle.
 * Otherwise you will receive a SIGSEGV
 */
static void unload_sort_function(void)
{
    if ( handle != NULL ) {
        /* Close our handle to the dynamic library. */
        if ( dlclose( handle ) != 0 ) {
            fprintf( stderr, "Failed to unload the library: %s\n", dlerror() );
        }
        else {
            handle = NULL;
        }
    }
}

/*
 * @brief Sort the array with the greater number first.
 */
static void inverse_sort_array(
    const char alg_name[],
    int array[],
    int array_count
)
{
    const char func_name[] = "inverse_sort";
    int first_index;
    int last_index;
    sort_func_ptr_t func_ptr;

    assert( alg_name != NULL );
    assert( array != NULL );
    assert( ( 0 < array_count ) && ( array_count < ARRAY_ITEMS_MAX_COUNT ) );

    first_index = 0;
    last_index = array_count - 1;

    func_ptr = load_sort_function( alg_name, func_name );
    if (func_ptr == NULL) {
        fprintf( stderr, "Could not load library: null function pointer\n" );
        exit(EXIT_FAILURE);
    }

    (*func_ptr)( array, first_index, last_index );

    unload_sort_function();
}

/*
 * @brief Prints the value of each array item.
 */
static void print_array(
    const int array[],
    const int array_count
)
{
    int i;

    assert( array != NULL );
    assert( ( 0 < array_count ) && ( array_count < ARRAY_ITEMS_MAX_COUNT ) );

    for ( i = 0; i < array_count; i++ ) {
        printf( "%d ", array[ i ] );
    }

    printf( "\n" );
}

int main(int argc, char *argv[])
{
    char *alg_name = "quicksort";
    int numbers[ ARRAY_ITEMS_COUNT ];
    int first_index;
    int last_index;
    int c;

    while ( ( c = getopt( argc, argv, "a:" ) ) != -1 ) {
        switch( c ) {
            case 'a':
                alg_name = optarg;
                break;
            case '?':
                printf( "Unrecognized option encountered -%c\n", optopt );
                exit( EXIT_FAILURE );
            default:
                exit( EXIT_FAILURE );
        }
    }

    memset( numbers, 0, sizeof(numbers) );

    first_index = 0;
    last_index = (int) ARRAY_COUNT( numbers ) - 1;

    init_array( numbers, (int) ARRAY_COUNT( numbers ) );
    assert( numbers[ first_index ] == first_index );
    assert( numbers[ last_index ] == last_index );
    print_array( numbers, (int) ARRAY_COUNT( numbers ) );

    inverse_sort_array( alg_name, numbers, (int) ARRAY_COUNT( numbers ) );
    assert( numbers[ first_index ] == last_index );
    assert( numbers[ last_index ] == first_index );
    print_array( numbers, (int) ARRAY_COUNT( numbers ) );

    return 0;
}
