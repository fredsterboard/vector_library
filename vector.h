#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdio.h>
#include <stdlib.h>

/* Scaling factor for vector size increase */
#define SCALING 2

/* Initial size of newly created vector */
#define INITIAL 4

/* Macro to make vector declaration more intuitive */
#define vector(identifier) vector_ ## identifier *

/* Macro to make initialization more intuitive */
#define new_vector(identifier) new_vector ## identifier()

/* Macro to free a vector */
#define free_vector(vector) do {free(vector->data); free(vector);} while (0)

/* MACRO THAT DEFINES VECTOR AND CORRESPONDING FUNCTIONS */
#define initial_vector(type_t, identifier)                                   \
                                                                             \
/* STRUCTURE DEFINING VECTOR */                                              \
typedef struct _vector_ ## identifier                                        \
{                                                                            \
    /* Array holding data */                                                 \
    type_t *data;                                                            \
                                                                             \
    /* Size parameters */                                                    \
    size_t curr_size;                                                        \
    size_t maxi_size;                                                        \
                                                                             \
    /* Methods */                                                            \
    void (*append)(struct _vector_ ## identifier *self, type_t x);           \
    void (*extend)(struct _vector_ ## identifier *self,                      \
        struct _vector_ ## identifier * input);                              \
    void (*set)(struct _vector_ ## identifier *self, int index, type_t x);   \
    type_t (*get)(struct _vector_ ## identifier *self, int index);           \
    type_t (*pop)(struct _vector_ ## identifier *self);                      \
    size_t (*size)(struct _vector_ ## identifier *self);                     \
    size_t (*max_size)(struct _vector_ ## identifier *self);                 \
                                                                             \
} vector_ ## identifier ;                                                    \
                                                                             \
/* FUNCTION PROTOTYPES */                                                    \
vector_ ## identifier *new_vector ## identifier();                           \
                                                                             \
void append_ ## identifier(vector_ ## identifier *self, type_t x);           \
void extend_ ## identifier(vector_ ## identifier *self,                      \
    vector_ ## identifier * input);                                          \
void set_ ## identifier(vector_ ## identifier *self, int index, type_t x);   \
type_t get_ ## identifier(vector_ ## identifier *self, int index);           \
type_t pop_ ## identifier(vector_ ## identifier *self);                      \
size_t size_ ## identifier(vector_ ## identifier *self);                     \
size_t max_size_ ## identifier(vector_ ## identifier *self);                 \
                                                                             \
/* INITIALIZE VECTOR */                                                      \
vector_ ## identifier *new_vector ## identifier()                            \
{                                                                            \
    /* Allocate memory */                                                    \
    vector_ ## identifier *result;                                           \
    result = (vector_ ## identifier *)                                       \
        malloc(sizeof(vector_ ## identifier));                               \
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
    result->append =     &append_ ## identifier;                             \
    result->extend =     &extend_ ## identifier;                             \
    result->set =           &set_ ## identifier;                             \
    result->get =           &get_ ## identifier;                             \
    result->pop =           &pop_ ## identifier;                             \
    result->size =         &size_ ## identifier;                             \
    result->max_size = &max_size_ ## identifier;                             \
                                                                             \
    /* return pointer to memory type */                                      \
    return result;                                                           \
}                                                                            \
                                                                             \
/* METHODS */                                                                \
                                                                             \
/* Appends value to Vector */                                                \
void append_ ## identifier(vector_ ## identifier *self, type_t x)            \
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
void extend_ ## identifier(vector_ ## identifier *self,                      \
    vector_ ## identifier * input)                                           \
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
void set_ ## identifier(vector_ ## identifier *self, int index, type_t x)    \
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
type_t get_ ## identifier(vector_ ## identifier *self, int index)            \
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
type_t pop_ ## identifier(vector_ ## identifier *self)                       \
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
size_t size_ ## identifier(vector_ ## identifier *self)                      \
{                                                                            \
    return self->curr_size;                                                  \
}                                                                            \
                                                                             \
/* Returns maximum size before needing to resize */                          \
size_t max_size_ ## identifier(vector_ ## identifier *self)                  \
{                                                                            \
    return self->maxi_size;                                                  \
}                                                                            
                                                                                                   
 
#endif  /* _VECTOR_H */