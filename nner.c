/*
 *  CKDatastruct
 *  Copyright http://cengek.com
 *
 *  Coded by @igrir
 *
 *  
 */

#include "nner.h"


//QUEUEUEUEUEUEUEUE


void createEmpty(queue *Q){
    (*Q).first = NULL;
    (*Q).last = NULL;
    (*Q).jumlahElemen = 0;
}

int isEmpty(queue Q){
    if(Q.jumlahElemen == 0){
        return 1;
    }else{
        return 0;
    }
}

void add(queue *Q, simpul *s){
    elemen * baru = (elemen *) malloc(sizeof(elemen));
    baru->paket.s = (simpul *) malloc(sizeof(simpul));
    *(baru->paket.s) = *s;
    baru->next = NULL;
    if(isEmpty(*Q) == 1){
        (*Q).first = baru;
        (*Q).last = baru;
        
    }else{
        (*Q).last->next = baru;
        (*Q).last = baru;
    }
    
    (*Q).jumlahElemen++;
}

void del(queue * Q){
    if(isEmpty(*Q) == 0){
        elemen * hapus = (*Q).first;
        if((*Q).jumlahElemen == 1){
            (*Q).first = NULL;
            (*Q).last = NULL;
            (*Q).jumlahElemen--;
            free(hapus);
        }else{
            (*Q).first = hapus->next;
            (*Q).jumlahElemen--;
            hapus->next = NULL;
            free(hapus);
        }        
    }
}

void printElement(queue Q){
    elemen * now = Q.first;
    if(now != NULL){
        do{
            printf("%c\n", now->paket.s->c);
            now = now->next;
        }while(now != NULL);
    }
    
}



//akhir dari QUEUEUEUUE


void makeTree(tree *T, char c) {
    simpul * baru = (simpul*) malloc (sizeof(simpul));
    baru->c=c;
    baru->sibling=NULL;
    (*T).root = baru;
}

void addChild(simpul* S, char c){
    if(S != NULL){
        simpul * baru = (simpul*)malloc(sizeof(simpul));
        baru->c = c;
        //gak punya anak
        //punya anak1
        //punya anak lebih dari 1
        if(S->child == NULL){
            S->child = baru;
            baru->child = NULL;
            baru->sibling= NULL;
        }else if(S->child != NULL){
            if(S->child->sibling == NULL){
                S->child->sibling = baru;
                baru->sibling = S->child;
                baru->child = NULL;
            }else{
                simpul * now = S->child;
                while(now->sibling != S->child){
                    now = now->sibling;
                }
                now->sibling = baru;
                baru->sibling = S->child;
                baru->child = NULL;
            }
        }
    }
}

void delChild(simpul *S, char c){
    
    if (S != NULL) {
        if (S->child != NULL){
            //anak cuman 1
            //anaknya cuman 2
            //anaknya banyak
            
            if (S->child->sibling == NULL) {
                if (S->child->child == NULL) {
                    simpul * hapus = S->child;
                    S->child = NULL;
                    free(hapus);
                }
            }else{
                if (S->child->sibling->sibling == S->child) {
                    if(S->child->c == c){
                        if (S->child->child == NULL) {
                            simpul * hapus = S->child;
                            S->child = hapus->sibling;
                            hapus->sibling = NULL;
                            S->child->sibling = NULL;
                            free(hapus);
                        }
                    }
                    if (S->child->sibling->c == c) {
                        if (S->child->sibling->child == NULL) {
                            simpul * hapus = S->child->sibling;
                            hapus->sibling = NULL;
                            S->child->sibling = NULL;
                            free(hapus);
                        }
                    }
                }else{
                    simpul * prev = NULL;
                    simpul * hapus = S->child;
                    while ((hapus->c != c) && (hapus->sibling != S->child)) {
                        prev = hapus;
                        hapus = hapus->sibling;
                    }
                    if(hapus->c == c){
                        if (hapus->child == NULL) {
                            if (prev == NULL) {
                                prev = S->child;
                                while (prev->sibling != S->child) {
                                    prev = prev->sibling;
                                }
                                S->child = hapus->sibling;
                            }
                        }
                        prev->sibling = hapus->sibling;
                        hapus->sibling = NULL;
                        free(hapus);
                    }
                }
            }
            
        }
    }
}

void printTreePreOrder(simpul * S) {
    if (S != NULL) {
        printf("%c ", S->c);
        if (S->child != NULL) {
            if (S->child->sibling == NULL) {
                printTreePreOrder(S->child);
            }else{
                simpul * now = S->child;
                while (now->sibling != S->child) {
                    printTreePreOrder(now);
                    now = now->sibling;
                }
                //untuk yang terakhir
                printTreePreOrder(now);
            }
        }
    }
}

void printTreePostOrder(simpul * S) {
    if (S != NULL) {
        if (S->child != NULL) {
            if (S->child->sibling == NULL) {
                printTreePostOrder(S->child);
            }else{
                simpul * now = S->child;
                while (now->sibling != S->child) {
                    printTreePostOrder(now);
                    now = now->sibling;
                }
                //untuk yang terakhir
                printTreePostOrder(now);
            }
        }
        printf("%c ", S->c);
    }
}

void printTreeLevelOrder(simpul* S) {
    
    if (S != NULL) {
        
        //buat penampung data yang akan dicek
        //antrianNodes ini menampung child dari node yang diproses
        queue antrianNodes;
        createEmpty(&antrianNodes);
        
        //masukkan dulu root dari pencarian agar menjadi acuan pertama
        //dicek
        add(&antrianNodes, S);
        
        //mulai memproses childs
        
        //lakukan selama queue child yang harus diproses belum kosong
        //ini berarti masih ada child yang harus diproses
        while (isEmpty(antrianNodes) != 1) {
            
            //tampilkan isinya
            printf("%c,", antrianNodes.first->paket.s->c);
            
            simpul * now = antrianNodes.first->paket.s;
            
            simpul * nodePertama = now;
            
            
            //jika punya anak
            //masukkan child dari node alamat di queue ke dalam queue sekarang
            
            if(now->child != NULL){
                simpul * nowchild = now->child;
                
                //jika punya saudara
                if(nowchild->sibling != NULL){
                    
                    //looping memasukkan anak-anak
                    while (nowchild->sibling != now->child) {
                        add(&antrianNodes, nowchild);
                        nowchild = nowchild->sibling;
                    }
                    //masukkan yang terakhir
                    add(&antrianNodes, nowchild);
                }else{
                    //tak punya saudara masukkan saja satu
                    add(&antrianNodes, nowchild);
                }
            }
            
            del(&antrianNodes);
        }
    }
}