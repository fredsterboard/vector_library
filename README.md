# vector_library
Vector implementation in C

-----------------------------------------------------------------------------
vector.h is a vector library that supports vectors of different types.

From initial testing, it seems that this library outperforms std::vector.
However, further benchmark tests are warranted to compare performance.

Either way, here's an explanation of how to use the library as currently
implemented.
-----------------------------------------------------------------------------
SCALING FACTOR:
The default scaling factor for which the maximum size of a vector grows is 
currently set to 2. To change the scaling factor, either change the value 
for SCALING in vector.h or include the following lines in your code:
```
#undef SCALING
#define SCALING 2
```
-----------------------------------------------------------------------------
INITIAL SIZE:
When a vector is declared and initialized, the maximum size of the vector is 
set to 4. To change this initial size, either change the value for INITIAL in
vector.h or include the following lines in your code:
```
#undef INITIAL
#define INITIAL 4
```
-----------------------------------------------------------------------------
INITIALIZING VECTOR TYPES:

To Initialize vectors of a certain type in your code, add the following line
after your preprocessor statements:

```
initial_vector(type_t, id);
```

type_t is the type of vector for which you plan to use in your code.

id is the unique identifier for which you plan to identify your vector type.

Example:

```
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

initial_vector(int, integer);

int main(void)
{ 
    /* Code goes here */
    return 0;
}
```

note: If you define your own type as usual with structs/enums/unions 
you must define the type before you initialize the 
vector of that type as such:

```
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

typedef struct _node
{
    int value;
    struct _node * next;
} node;

initial_vector(node *, node_p);

int main(void)
{ 
    /* Code goes here */
    return 0;
}
```

-----------------------------------------------------------------------------
CREATING A VECTOR:

After you initialize the desired vector type, you can 
create a vector in the following way:


```
vector(id) x = new_vector(id); 
```


alternatively you can write:


```
vector_id *x = new_vector(type_t);
```

-----------------------------------------------------------------------------

```
vector(id) x; 
```

declares a pointer x of type vector(id) that holds a resizeable array of type_ts.

```
x = new_vector(id); 
```

Allocates memory to x and sets all of x's methods.

Example:

```
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

initial_vector(int, integer);

int main(void)
{ 
    vector(integer) x = new_vector(integer);

    /* Do stuff */

    return 0;
}
```
-----------------------------------------------------------------------------
FREEING A VECTOR:

Once you are done with the vector that you created, you can free it in the
following way:

```
free_vector(x);
```

Example:

```
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

initial_vector(int, integer);

int main(void)
{ 
    vector(integer) x = new_vector(integer);

    /* Do stuff */

    free_vector(x);
    return 0;
}
```

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

```
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

initial_vector(int, integer);
initial_vector(float, fl)

int main(void)
{ 
    int i;
    
    vector(integer) x = new_vector(integer);
    vector(integer) y = new_vector(integer);
    vector(fl) z = new_vector(fl);

    for(i = 0; i < 314; i++)
    {
        x->append(x, i);
        y->append(z, float(i));
    }

    y->extend(y,x);

    for(i = 0; i < y->size(y); i++)
    {
        printf("%d\n", y->get(y, i));
        printf("%f\n", z->get(y, i));
    }


    printf("curr_size: %zu\n", y->size(y));
    printf("maxi_size: %zu\n", y->max_size(y));

    free_vector(x);
    free_vector(y);

    return 0;
}
```









