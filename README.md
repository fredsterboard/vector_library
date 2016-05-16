# vector_library
Vector implementation in C




vector.h is a vector library that supports vectors of different types.

-----------------------------------------------------------------------------
SCALING FACTOR:
The default scaling factor for which the maximum size of a vector grows is 
currently set to 2. To change the scaling factor, either change the value 
for SCALING in vector.h or include the following lines in your code:
'''
#undef SCALING
#define SCALING 2
'''
-----------------------------------------------------------------------------
INITIAL SIZE:
When a vector is declared and initialized, the maximum size of the vector is 
set to 4. To change this initial size, either change the value for INITIAL in
vector.h or include the following lines in your code:
'''
#undef INITIAL
#define INITIAL 4
'''
-----------------------------------------------------------------------------
INITIALIZING VECTOR TYPES:

To Initialize vectors of a certain type in your code, add the following line
after your preprocessor statements:

'''
initial_vector(type_t);
'''

type_t is the type of vector for which you plan to use in your code:

Example:
'''
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

initial_vector(int);

int main(void)
{ 
    /* Code goes here */
    return 0;
}
'''
note: If you define your own type as usual with structs/enums/unions, 
you must define the type before you initialize the vector of that type.
-----------------------------------------------------------------------------
CREATING A VECTOR:

After you initialize the desired vector type, you can 
create a vector in the following way:


'''
vector(type_t) x = new_vector(type_t); 
'''


alternatively you can write:


'''
vector(type_t) x;
x = new_vector(type_t);
'''

'''
vector(type_t) x; 
'''
declares a pointer x of type vector(type_t) that holds a
                  resizeable array of type_ts.
'''
x = new_vector(type_t); 
'''
Allocates memory to x and sets all of x's methods.

Example:
'''
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

initial_vector(int);

int main(void)
{ 
    vector(int) x = new_vector(int);
    /* Do stuff */
    return 0;
}
'''
-----------------------------------------------------------------------------
FREEING A VECTOR:

Once you are done with the vector that you created, you can free it in the
following way:
'''
free_vector(type_t, x);
'''
type_t is the element type within the vector and x is the pointer to the
vector itself. An example would look like the following:

Example:
'''
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

initial_vector(int);

int main(void)
{ 
    vector(int) x = new_vector(int);
    /* Do stuff */
    free_vector(int, x);
    return 0;
}
'''
-----------------------------------------------------------------------------
CALLING METHODS:

There are currently 7 methods supported by the current implementation of the
vector.h library:

append: adds an element of supported type to the vector:
    arguments: self, element
    return: void

extend: adds the contents from another vector to the vector.
    arguments: self, other_vector
    return: void

set: changes the value of the element in the vector of a given index.
    arguments: self, index, element
    return: void

get: gets the value of an element in the vector of a given index.
    arguments: self, index
    return: type_t

pop: pops the last element of the vector:
    arguments: self
    return: type_t

size: gives the current size of the vector array
    arguments: self
    return: size_t

max_size: gives the max size the vector can be before memory reallocation
    arguments: self
    return: size_t

Example of method calls:
'''
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

initial_vector(int);

int main(void)
{ 
    int i;
    
    vector(int) x = new_vector(int);
    vector(int) y = new_vector(int);

    for(i = 0; i < 314; i++)
    {
        x->append(x, i);
    }

    y->extend(y,x);

    for(i = 0; i < y->size(y); i++)
        printf("%d\n", y->get(y, i));

    printf("curr_size: %zu\n", y->size(y));
    printf("maxi_size: %zu\n", y->max_size(y));

    free_vector(int, x);
    free_vector(int, y);
    return 0;
}
'''









