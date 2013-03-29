bin_PROGRAMS = exercicio1 exercicio2 exercicio3 exercicio4 exercicioII3
lib_LTLIBRARIES = libquicksort.la libinsertionsort.la

AM_CFLAGS = -g -Wall -Wextra -Wshadow -Wswitch-default -Wfloat-equal \
-Wcast-qual -Wconversion -pedantic -ansi -D_GNU_SOURCE
AM_LDFLAGS = -ldl -rdynamic

exercicio1_SOURCES = exercicio1.c
exercicio2_SOURCES = exercicio2.c quicksort.h
libquicksort_la_SOURCES = sort.h quicksort.c
libinsertionsort_la_SOURCES = sort.h insertionsort.c
exercicio3_SOURCES = exercicio3.c statemachine.h statemachine_logic.c statemachine_table.c
exercicio4_SOURCES = exercicio4.c linkedlist.c linkedlist.h
exercicioII3_SOURCES = exercicioII3.c
