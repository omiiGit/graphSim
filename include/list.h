#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

#define PRINT_int(a) (printf("%d ",a))
#define PRINT_float(a) (printf("%g ",a))
#define PRINT_double(a) (printf("%g ",a))

typedef struct Node
{
    struct Node* next;
    struct Node* prev;
    void* data;
}Node;

typedef struct 
{
    Node* head;
    Node* tail;
    int count;
}List;

static Node createNode()
{    
    return(Node)
    {
        .next = NULL,
        .prev = NULL,
        .data = NULL,
    };
}

static List createList()
{
    return(List)
    {
        .head = NULL,
        .tail = NULL,
        .count = 0,
    };
}

#define LIST_ADD(type,list,value)\
do{\
    Node* __t = (Node*)malloc(sizeof(Node));\
    *__t = createNode();\
    type* p = (type*)malloc(sizeof(type));\
    *p = (value);\
    __t->data = p;\
\
    if((list)->count == 0)\
    {\
        (list)->head = __t;\
        (list)->tail = __t;\
    }\
    else\
    {\
        (list)->tail->next = __t;\
        __t->prev = (list)->tail;\
        (list)->tail = __t;\
    }\
\
    (list)->count++;\
}while(0)\

#define LIST_GET(type,list,pos)\
({\
    Node* __t = (list)->head;\
\
    for(int __i = 0;__i < (pos);__i++)\
    {\
        __t = __t->next;\
    }\
\
    *((type*)__t->data);\
})\

#define LIST_DEL(type,list,pos)\
do{\
    if((pos) == 0)\
    {\
        Node* __j = (list)->head;\
        (list)->head = (list)->head->next;\
        free(__j);\
    }\
    else if((pos) == (list)->count - 1)\
    {\
        Node* __j = (list)->tail;\
        (list)->tail = (list)->tail->next;\
        free(__j);\
    }\
    else\
    {\
        Node* __j = (list)->head;\
\
        for(int __k = 0;__k < (pos);__k++)\
        {\
            __j = __j->next;\
        }\
\
        __j->prev->next = __j->next;\
        __j->next->prev = __j->prev;\
        free(__j);\
    }\
    (list)->count--;\
}while(0)\

#define LIST_FLUSH(type,list)\
do{\
    int i = (list)->count;\
\
    for(int __o = 0;__o < i;__o++)\
    {\
        LIST_DEL((type),(list),0);\
    }\
}while(0)\

#define PRINT_LIST(type,list)\
do{\
    if((list)->count) == 0)\
    {\
        printf("List is empty\n");\
    }\
    else\
    {\
        for(int __j = 0;__j < (list)->count;__j++)\
        {\
            PRINT_##type(LIST_GET(type,(list),__j));\
        }\
    }\
}while(0)\

#endif
