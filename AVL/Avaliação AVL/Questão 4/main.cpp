#include <iostream>
#include "avl.h"
using namespace std;

int main() {
    system ("chcp 65001 > nul");
    avl_tree *t = new avl_tree;
    avl_tree *t2 = new avl_tree;
    avl_tree *t3 = new avl_tree;

    for(int i = 1; i <= 20; i++) {
        if (i % 2 == 0)
            t->add(i);
    }

    for(int i = 1; i <=20; i++) {
        if (i % 2 != 0)
            t2->add(i);
    }
    
    t3->enchePilha(t, t2, t3);
    t->bshow();
    t2->bshow();
    t3->bshow();

}