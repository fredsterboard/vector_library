#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#undef SCALING
#define SCALING 1.24 /* Someone once told me this is the best */

initial_vector(int, int);

int main(void)
{ 
    int i;

    /* Both ways work */
    vector(int) x = new_vector(int);
    vector_int *y = new_vector(int);

    for(i = 0; i < 314; i++)
    {
        x->append(x, i);
    }

    y->extend(y,x);

    for(i = 0; i < y->size(y); i++)
        printf("%d\n", y->get(y, i));

    printf("curr_size: %zu\n", y->size(y));
    printf("maxi_size: %zu\n", y->max_size(y));
    
    free_vector(x);
    free_vector(y);
    return 0;
}