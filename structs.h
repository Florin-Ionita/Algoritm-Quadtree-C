#ifndef _STRUCTS_
#define _STRUCTS_

typedef struct RGB {
    unsigned char red;
    unsigned char blue;
    unsigned char green;
} Color;

typedef struct node {

    unsigned char type;
    Color color;
    int size;
    struct node *first;
    struct node *second;
    struct node *third;
    struct node *fourth;
    // Prefer in loc de un vector de pointer sa numesc fiecare nod in parte

} *Tree;

typedef struct list{
    Tree valoare;
    struct list *next;
} *List;

typedef struct queue {
    List front, rear;
} Queue;

#endif // _STRUCTS_