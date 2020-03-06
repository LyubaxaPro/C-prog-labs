#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct node
{
    int num;
    int degree;
    struct node *p_next;
}node;

typedef struct
{
    node *head;
    node *tail;
}digit;

#endif