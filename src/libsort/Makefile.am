lib_LTLIBRARIES = libquicksort.la libinsertionsort.la libmergesort.la

AM_CFLAGS = -g -Wall -Wextra -Wshadow -Wswitch-default -Wfloat-equal \
            -Wcast-qual -Wconversion -pedantic -ansi -D_GNU_SOURCE \
             -fprofile-arcs -ftest-coverage
AM_LDFLAGS = -pg -lgcov

libquicksort_la_SOURCES = sort.h quicksort.c
libinsertionsort_la_SOURCES = sort.h insertionsort.c
libmergesort_la_SOURCES = sort.h mergesort.c
