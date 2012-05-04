#include <stdio.h>
#include "nner.h"

int main() {
    tree T;
    makeTree( &T, 'A');
    addChild(T.root, 'B');
    addChild(T.root, 'C');
    addChild(T.root, 'D');
    addChild(T.root->child, 'E');
    addChild(T.root->child, 'F');
    addChild(T.root->child->sibling, 'G');

    printf("Level Order\n");
    printTreeLevelOrder(T.root);
    printf("\n");
    return 0;
}