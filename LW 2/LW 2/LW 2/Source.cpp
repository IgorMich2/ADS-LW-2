/*#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include "BBST.h"
using namespace std;

int main()
{
    int choice, item;
    avlTree<char> avl;
    cout << avl.isempty(root) << endl;
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
    cout << endl;
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
*/
#include <algorithm>
#include <iostream>
using namespace std;
/* AVL node */
template <class T>
class AVLnode {
public:
    T key;
    int balance;
    AVLnode* left, * right, * parent;

    AVLnode(T k, AVLnode* p) : key(k), balance(0), parent(p),
        left(NULL), right(NULL) {}

    ~AVLnode() {
        delete left;
        delete right;
    }
};

/* AVL tree */
template <class T>
class AVLtree {
public:
    AVLtree(void);
    ~AVLtree(void);
    bool insert(T key);
    void deleteKey(const T key);
    void printBalance();
    void display(AVLnode<T>* ptr, int level);
    AVLnode<T>* root;
    void inorder(AVLnode<T>* tree);
    void preorder(AVLnode<T>* tree);
    void postorder(AVLnode<T>* tree);
    bool isempty(AVLnode<T>* tree);
    int height2(AVLnode<T>* temp);
    int diff(AVLnode<T>* temp);
    void search(AVLnode<T>* tree, T el);
    bool isfull(AVLnode<T>* tree);

private:
    

    AVLnode<T>* rotateLeft(AVLnode<T>* a);
    AVLnode<T>* rotateRight(AVLnode<T>* a);
    AVLnode<T>* rotateLeftThenRight(AVLnode<T>* n);
    AVLnode<T>* rotateRightThenLeft(AVLnode<T>* n);
    void rebalance(AVLnode<T>* n);
    int height(AVLnode<T>* n);
    void setBalance(AVLnode<T>* n);
    void printBalance(AVLnode<T>* n);
};

/* AVL class definition */
template <class T>
void AVLtree<T>::rebalance(AVLnode<T>* n) {
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T>* a) {
    AVLnode<T>* b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != NULL)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T>* a) {
    AVLnode<T>* b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != NULL)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T>* n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T>* n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <class T>
int AVLtree<T>::height(AVLnode<T>* n) {
    if (n == NULL)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}

template <class T>
void AVLtree<T>::setBalance(AVLnode<T>* n) {
    n->balance = height(n->right) - height(n->left);
}

template <class T>
void AVLtree<T>::printBalance(AVLnode<T>* n) {
    if (n != NULL) {
        printBalance(n->left);
        std::cout << n->balance << " ";
        printBalance(n->right);
    }
}

template <class T>
AVLtree<T>::AVLtree(void) : root(NULL) {}

template <class T>
AVLtree<T>::~AVLtree(void) {
    delete root;
}

template <class T>
bool AVLtree<T>::insert(T key) {
    if (root == NULL) {
        root = new AVLnode<T>(key, NULL);
    }
    else {
        AVLnode<T>
            * n = root,
            * parent;

        while (true) {
            if (n->key == key)
                return false;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}

template <class T>
void AVLtree<T>::deleteKey(const T delKey) {
    if (root == NULL)
        return;

    AVLnode<T>
        * n = root,
        * parent = root,
        * delNode = NULL,
        * child = root;

    while (child != NULL) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }

    if (delNode != NULL) {
        delNode->key = n->key;

        child = n->left != NULL ? n->left : n->right;

        if (root->key == delKey) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
    }
}

template <class T>
void AVLtree<T>::printBalance() {
    printBalance(root);
    std::cout << std::endl;
}

template< typename T >
void AVLtree<T>::display(AVLnode<T>* ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
            cout << "Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout << "        ";
        cout << ptr->key;
        display(ptr->left, level + 1);
    }
}




template< typename T >
void AVLtree<T>::inorder(AVLnode<T>* tree)
{
    if (tree == NULL)
        return;
    inorder(tree->left);
    cout << tree->key << "  ";
    inorder(tree->right);
}

template< typename T >
void AVLtree<T>::preorder(AVLnode<T>* tree)
{
    if (tree == NULL)
        return;
    cout << tree->key << "  ";
    preorder(tree->left);
    preorder(tree->right);

}

template< typename T >
void AVLtree<T>::postorder(AVLnode<T>* tree)
{
    if (tree == NULL)
        return;
    postorder(tree->left);
    postorder(tree->right);
    cout << tree->key << "  ";
}

template< typename T >
bool AVLtree<T>::isempty(AVLnode<T>* tree)
{
    if (tree == NULL)
        return true;
    else return false;
}

template< typename T >
bool AVLtree<T>::isfull(AVLnode<T>* tree)
{
    if (diff(tree) == 0)
        return true;
    else return false;
}

template< typename T >
void AVLtree<T>::search(AVLnode<T>* tree, T el)
{
    if (tree == NULL) {
        return;
    }

    search(tree->left, el);
    if (el == tree->key) {
        cout << "Element " << el << " is in the list" << "  ";
    }
    else search(tree->right, el);
}

template< typename T >
int AVLtree<T>::height2(AVLnode<T>* temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height2(temp->left);
        int r_height = height2(temp->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}


template< typename T >
int AVLtree<T>::diff(AVLnode<T>* temp)
{
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int b_factor = l_height - r_height;
    return b_factor;
}


int main(void)
{
    AVLtree<int> t;

    
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.display(t.root, 1);
    cout << endl;

    t.inorder(t.root);
    cout << endl;
    t.preorder(t.root);
    cout << endl;
    t.postorder(t.root);
    cout << endl;
    cout << t.isempty(t.root);
    cout << endl;
    t.search(t.root, 1);
    cout << endl;
    cout <<"Height "<<  t.height2(t.root);
    cout << endl;
    cout << "Is full " << t.isfull(t.root);
    cout << endl;
    cout << "Diff " << t.diff(t.root);
    cout << endl;

    t.printBalance();
    cout << endl;


    AVLtree<string> s;


    s.insert("sa");
    s.insert("ab");
    s.insert("cd");

    s.printBalance();
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    s.display(s.root, 1);


}
