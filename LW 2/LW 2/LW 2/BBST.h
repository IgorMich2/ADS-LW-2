#pragma once
#ifndef _BBST_H
#define _BBST_H
#include<iostream>

using namespace std;
/*
//Node Declaration
//template< typename T >
struct avl_node
{
    int data;
    struct avl_node* left;
    struct avl_node* right;
}*root;


//Class Declaration
template< typename T >
class avlTree
{
public:
    int height(avl_node*);
    int diff(avl_node*);
    avl_node* rr_rotation(avl_node*);
    avl_node* ll_rotation(avl_node*);
    avl_node* lr_rotation(avl_node*);
    avl_node* rl_rotation(avl_node*);
    avl_node* balance(avl_node*);
    avl_node* insert(avl_node*, int);

    void inorder(avl_node*);
    void preorder(avl_node*);
    void postorder(avl_node*);
    void search(avl_node*, int el);
    bool isempty(avl_node*);
    avlTree()
    {
        root = NULL;
    }
};




// Right- Right Rotation
template< typename T >
avl_node* avlTree<T>::rr_rotation(avl_node* parent)
{
    avl_node* temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

// Left- Left Rotation
template< typename T >
avl_node* avlTree<T>::ll_rotation(avl_node* parent)
{
    avl_node* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}


// Left - Right Rotation
template< typename T >
avl_node* avlTree<T>::lr_rotation(avl_node* parent)
{
    avl_node* temp;
    temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}


// Right- Left Rotation
template< typename T >
avl_node* avlTree<T>::rl_rotation(avl_node* parent)
{
    avl_node* temp;
    temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}


//Balancing AVL Tree
template< typename T >
avl_node* avlTree<T>::balance(avl_node* temp)
{
    int bal_factor = diff(temp);
    if (bal_factor > 1)
    {
        if (diff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    }
    else if (bal_factor < -1)
    {
        if (diff(temp->right) > 0)
            temp = rl_rotation(temp);
        else
            temp = rr_rotation(temp);
    }
    return temp;
}

// Insert Element into the tree
template< typename T >
avl_node* avlTree<T>::insert(avl_node* root, int value)
{
    if (root == NULL)
    {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->data)
    {
        root->left = insert(root->left, value);
        root = balance(root);
    }
    else if (value >= root->data)
    {
        root->right = insert(root->right, value);
        root = balance(root);
    }
    return root;
}
*/


#endif