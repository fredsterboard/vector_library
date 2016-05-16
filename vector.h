#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdio.h>
#include <stdlib.h>

/* Scaling factor for vector size increase */
#define SCALING 2

/* Initial size of newly created vector */
#define INITIAL 1

/* Macro to make vector declaration more intuitive */
#define vector(type_t) vector_ ## type_t *

/* Macro to make initialization more intuitive */
#define new_vector(type_t) new_vector ## type_t ()

#define free_vector(type_t, vector) free_vector_ ## type_t (vector)

/* MACRO THAT DEFINES VECTOR AND CORRESPONDING FUNCTIONS */
#define initial_vector(type_t)                                               \
                                                                             \
/* STRUCTURE DEFINING VECTOR */                                              \
typedef struct _vector_ ## type_t                                            \
{                                                                            \
    /* Array holding data */                                                 \
    type_t *data;                                                            \
                                                                             \
    /* Size parameters */                                                    \
    size_t curr_size;                                                        \
    size_t maxi_size;                                                        \
                                                                             \
    /* Methods */                                                            \
    void (*append)(struct _vector_ ## type_t *self, type_t x);               \
    void (*extend)(struct _vector_ ## type_t *self,                          \
        struct _vector_ ## type_t * input);                                  \
    void (*set)(struct _vector_ ## type_t *self, int index, type_t x);       \
    type_t (*get)(struct _vector_ ## type_t *self, int index);               \
    type_t (*pop)(struct _vector_ ## type_t *self);                          \
    size_t (*size)(struct _vector_ ## type_t *self);                         \
    size_t (*max_size)(struct _vector_ ## type_t *self);                     \
                                                                             \
} vector_ ## type_t ;                                                        \
                                                                             \
/* FUNCTION PROTOTYPES */                                                    \
vector_ ## type_t *new_vector ## type_t ();                                  \
void free_vector_ ## type_t (vector_ ## type_t *vector);                     \
                                                                             \
void append_ ## type_t (vector_ ## type_t *self, type_t x);                  \
void extend_ ## type_t (vector_ ## type_t *self, vector_ ## type_t * input); \
void set_ ## type_t (vector_ ## type_t *self, int index, type_t x);          \
type_t get_ ## type_t (vector_ ## type_t *self, int index);                  \
type_t pop_ ## type_t (vector_ ## type_t *self);                             \
size_t size_ ## type_t (vector_ ## type_t *self);                            \
size_t max_size_ ## type_t (vector_ ## type_t *self);                        \
                                                                             \
/* INITIALIZE VECTOR */                                                      \
vector_ ## type_t *new_vector ## type_t ()                                   \
{                                                                            \
    /* Allocate memory */                                                    \
    vector_ ## type_t *result;                                               \
    result = (vector_ ## type_t *)malloc(sizeof(vector_ ## type_t));         \
    if (result == NULL)                                                      \
    {                                                                        \
        fprintf(stderr, "Memory allocation failure!\n");                     \
        exit(1);                                                             \
    }                                                                        \
    result->data = (type_t *)calloc(INITIAL, sizeof(type_t));                \
    if (result->data == NULL)                                                \
    {                                                                        \
        fprintf(stderr, "Memory allocation failure!\n");                     \
        exit(1);                                                             \
    }                                                                        \
    result->curr_size = 0;                                                   \
    result->maxi_size = INITIAL;                                             \
                                                                             \
    /* Setting appropriate function pointers to work as methods */           \
    result->append =     &append_ ## type_t;                                 \
    result->extend =     &extend_ ## type_t;                                 \
    result->set =           &set_ ## type_t;                                 \
    result->get =           &get_ ## type_t;                                 \
    result->pop =           &pop_ ## type_t;                                 \
    result->size =         &size_ ## type_t;                                 \
    result->max_size = &max_size_ ## type_t;                                 \
                                                                             \
    /* return pointer to memory type */                                      \
    return result;                                                           \
}                                                                            \
                                                                             \
/* Frees vector when done using it */                                        \
void free_vector_ ## type_t (vector_ ## type_t *vector)                      \
{                                                                            \
    free(vector->data);                                                      \
    free(vector);                                                            \
}                                                                            \
                                                                             \
/* METHODS */                                                                \
                                                                             \
/* Appends value to Vector */                                                \
void append_ ## type_t (vector_ ## type_t *self, type_t x)                   \
{                                                                            \
    if (self->curr_size == self->maxi_size)                                  \
    {                                                                        \
        self->maxi_size *= SCALING;                                          \
        self->maxi_size++;                                                   \
        self->data = (type_t *)realloc(self->data,                           \
            self->maxi_size * sizeof(type_t));                               \
        if (self->data == NULL)                                              \
        {                                                                    \
            fprintf(stderr, "Memory reallocation failure!\n");               \
            exit(1);                                                         \
        }                                                                    \
    }                                                                        \
    self->data[self->curr_size] = x;                                         \
    self->curr_size++;                                                       \
}                                                                            \
                                                                             \
/* Extends a vector with the values of a given vector of the same type */    \
void extend_ ## type_t (vector_ ## type_t *self, vector_ ## type_t * input)  \
{                                                                            \
    int i;                                                                   \
    while ((self->maxi_size - self->curr_size) < input->curr_size)           \
    {                                                                        \
        self->maxi_size *= SCALING;                                          \
        self->maxi_size++;                                                   \
        self->data = (type_t *)realloc(self->data,                           \
            self->maxi_size * sizeof(type_t));                               \
        if (self->data == NULL)                                              \
        {                                                                    \
            fprintf(stderr, "Memory reallocation failure!\n");               \
            exit(1);                                                         \
        }                                                                    \
    }                                                                        \
    for (i = 0; i < input->curr_size; i++)                                   \
    {                                                                        \
        self->data[self->curr_size] = input->data[i];                        \
        self->curr_size++;                                                   \
    }                                                                        \
}                                                                            \
                                                                             \
/* Sets value at index to new value */                                       \
void set_ ## type_t (vector_ ## type_t *self, int index, type_t x)           \
{                                                                            \
    if(index >= self->curr_size || index < 0)                                \
    {                                                                        \
        fprintf(stderr, "Index out of range!\n");                            \
        exit(1);                                                             \
    }                                                                        \
    self->data[index] = x;                                                   \
}                                                                            \
                                                                             \
/* Gets value at given index */                                              \
type_t get_ ## type_t (vector_ ## type_t *self, int index)                   \
{                                                                            \
    if(index >= self->curr_size || index < 0)                                \
    {                                                                        \
        fprintf(stderr, "Index out of range!\n");                            \
        exit(1);                                                             \
    }                                                                        \
    return self->data[index];                                                \
}                                                                            \
                                                                             \
/* Pops vector */                                                            \
type_t pop_ ## type_t (vector_ ## type_t *self)                              \
{                                                                            \
    if (self->curr_size == 0)                                                \
    {                                                                        \
        fprintf(stderr, "Cannot pop with vector size of zero!\n");           \
        exit(1);                                                             \
    }                                                                        \
    self->curr_size--;                                                       \
    return self->data[self->curr_size + 1];                                  \
}                                                                            \
                                                                             \
/* Returns current size of vector */                                         \
size_t size_ ## type_t (vector_ ## type_t *self)                             \
{                                                                            \
    return self->curr_size;                                                  \
}                                                                            \
                                                                             \
/* Returns maximum size before needing to resize */                          \
size_t max_size_ ## type_t (vector_ ## type_t *self)                         \
{                                                                            \
    return self->maxi_size;                                                  \
}                                                                            
                                                                                                   
 
#endif  /* _VECTOR_H */