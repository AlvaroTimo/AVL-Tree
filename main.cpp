#include <iostream>
#include "AVL.h"
using namespace std;

int main(){
    AVL_Tree<int> avl;
    avl.insert(10);
    avl.insert(4);
    avl.insert(5);
    // avl.insert(17);
    // avl.insert(8);
    // avl.insert(9);
    avl.print();
    return 0;
}