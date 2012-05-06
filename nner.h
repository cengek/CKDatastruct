#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct smp * alamattree;
typedef struct smp {
    char c;
    alamattree sibling;
    alamattree child;
}simpul;

typedef struct {
    simpul * root;
}tree;

void makeTree(tree*, char);
void addChild(simpul*, char);
void delChild(simpul*, char);
void printTreePreOrder(simpul*);
void printTreePostOrder(simpul*);
void printTreeLevelOrder(simpul*);

//BUAT QUEUE

typedef struct {
    simpul * s;
}isi;

typedef struct elmt * alamatq;

typedef struct elmt {
    isi paket;
    alamatq next;
}elemen;

typedef struct {
    elemen *first;
    elemen *last;
    int jumlahElemen;
}queue;

void createEmpty(queue *);
int isEmpty(queue);
void add(queue *Q, simpul *s);
void del(queue*);
