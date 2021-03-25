
#include <algorithm>
#include <iostream>
#include <queue>
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
    bool isbalanced(AVLnode<T>* tree);
    int height2(AVLnode<T>* temp);
    int diff(AVLnode<T>* temp);
    void search(AVLnode<T>* tree, T el);
    bool isfull(AVLnode<T>* tree);
    int height3(AVLnode<T>* n);
    int max(int a, int b);
    AVLnode<T>* rotateLeft(AVLnode<T>* a);
    AVLnode<T>* rotateRight(AVLnode<T>* a);
    AVLnode<T>* rotateLeftThenRight(AVLnode<T>* n);
    AVLnode<T>* rotateRightThenLeft(AVLnode<T>* n);
    void rebalance(AVLnode<T>* n);
    int height(AVLnode<T>* n);
    void setBalance(AVLnode<T>* n);
    void printBalance(AVLnode<T>* n);
    void reverseLevelOrder(AVLnode<T>* n);
    void printGivenLevel(AVLnode<T>* n, int level);
    unsigned int getfullCount(struct AVLnode<T>* node);
    int sum(AVLnode<T>* root);
    void deleteeven(AVLnode<T>* node);


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
void AVLtree<T>::reverseLevelOrder(AVLnode<T>* n)
{
    int h = height(root);
    int i;
    for (i = h+1; i >= 1; i--) //THE ONLY LINE DIFFERENT FROM NORMAL LEVEL ORDER 
        printGivenLevel(n, i);
}

template <class T>
void AVLtree<T>::deleteeven(AVLnode<T>* node)
{
    /*int h = height(root);
    int i;
    for (i = h + 1; i >= 1; i--) { //THE ONLY LINE DIFFERENT FROM NORMAL LEVEL ORDER 
        if (node == NULL)
            return;

        AVLnode<T>
            * n = node,
            * parent = node,
            * delNode = NULL,
            * child = node;

        while (child != NULL) {
            parent = n;
            n = child;
            child = node >= n->key ? n->right : n->left;
            if (node == n->key)
                delNode = n;
        }

        if (delNode != NULL) {
            delNode->key = n->key;

            child = n->left != NULL ? n->left : n->right;

            if (root->key == node) {
                node = child;
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
    }*/
}


/* Print nodes at a given level */
template <class T>
void AVLtree<T>::printGivenLevel(AVLnode<T>* n, int level)
{
    if (n == NULL)
        return;
    if (level == 1)
        cout << n->key << " ";
    else if (level > 1)
    {
        printGivenLevel(n->left, level - 1);
        printGivenLevel(n->right, level - 1);
    }
}
template <class T>
int AVLtree<T>::sum(AVLnode<T>* root)
{
    if (root == NULL)
        return 0;
    return (root->key + sum(root->left) + sum(root->right));
}


template <class T>
unsigned int AVLtree<T>::getfullCount(struct AVLnode<T>* node)
{
    // If tree is empty
    if (!node)
        return 0;
    queue<AVLnode<T>*> q;

    // Do level order traversal starting from root
    int count = 0; // Initialize count of full nodes
    q.push(node);
    while (!q.empty())
    {
        struct AVLnode<T>* temp = q.front();
        q.pop();

        if (temp->left && temp->right)
            count++;

        if (temp->left != NULL)
            q.push(temp->left);
        if (temp->right != NULL)
            q.push(temp->right);
    }
    return count;
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
int AVLtree<T>::max(int a, int b)
{
    return (a >= b) ? a : b;
}

template <class T>
int AVLtree<T>::height3(AVLnode<T>* node)
{
    /* base case tree is empty */
    if (node == NULL)
        return 0;

    /* If tree is not empty then
    height = 1 + max of left
        height and right heights */
    return 1 + max(height(node->left),
        height(node->right));
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
bool AVLtree<T>::isbalanced(AVLnode<T>* tree)
{
   // int lh; /* for height of left subtree */
   // int rh; /* for height of right subtree */

    /* If tree is empty then return true */
   // if (root == NULL)
        return 1;

    /* Get the height of left and right sub trees */
   // lh = tree.diff(tree);

   // if (abs(lh) <= 1 && isbalanced(tree))
        return 1;
        
    /* If we reach here then
    tree is not height-balanced */
    return 0;
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
    t.insert(5);
    t.insert(6);
    t.insert(7);
    t.display(t.root, 1);
    cout << endl;
    t.reverseLevelOrder(t.root);
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
    t.getfullCount(t.root);

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
    cout << t.isbalanced(t.root)<<endl;
    cout << t.getfullCount(t.root)<<endl;
    cout << t.sum(t.root) << endl;
    t.deleteeven(t.root);

}
