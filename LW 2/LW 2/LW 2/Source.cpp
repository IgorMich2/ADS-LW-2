/*
 * C++ program to Implement AVL Tree
 */
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include "BBST.h"
using namespace std;

/*
 * Main Contains Menu
 */
int main()
{
    int choice, item;
    avlTree avl;
    cout<<avl.isempty(root)<<endl;
    avl.display(root, 1);
    root = avl.insert(root, 1);
    root = avl.insert(root, 2);
    root = avl.insert(root, 3);
    root = avl.insert(root, 4);
    root = avl.insert(root, 5);
    root = avl.insert(root, 6);
    root = avl.insert(root, 7);
    root = avl.insert(root, 8);
    root = avl.insert(root, 9);
    root = avl.insert(root, 10);
    root = avl.insert(root, 11);
    root = avl.insert(root, 12);
    root = avl.insert(root, 13);
    root = avl.insert(root, 14);
    root = avl.insert(root, 15);
    root = avl.insert(root, 16);

    avl.display(root, 1);
    cout<< endl;
    avl.inorder(root);
    cout << endl;
    avl.preorder(root);
    cout << endl;
    avl.postorder(root);
    cout << endl;
    cout << avl.height(root);
    cout << endl;
    cout << avl.diff(root);
    cout << endl;
    cout << avl.isempty(root);
    cout << endl;

    avl.search(root, 123);
    cout << endl;

    return 0;
}
