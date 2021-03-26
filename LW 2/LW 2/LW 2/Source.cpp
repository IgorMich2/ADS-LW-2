
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

template <typename T>
    vector<T> a;
template <typename T>
    vector<T> un;
template <typename T>
    vector<T> dup;
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
    AVLnode<T>* newNode(int key);
        AVLnode<T>* copyLeftRightNode(AVLnode<T>* treeNode, unordered_map<AVLnode<T>*, AVLnode<T>*>& mymap);
    void inorder(AVLnode<T>* tree);
    void preorder(AVLnode<T>* tree);
    void postorder(AVLnode<T>* tree);
    bool isempty(AVLnode<T>* tree);
    bool isbalanced(AVLnode<T>* tree);
    int diff(AVLnode<T>* temp);
    void search(AVLnode<T>* tree, T el);
    bool isfull(AVLnode<T>* tree);
    int max(int a, int b);
    AVLnode<T>* rotateLeft(AVLnode<T>* a);
    AVLnode<T>* rotateRight(AVLnode<T>* a);
    AVLnode<T>* rotateLeftThenRight(AVLnode<T>* n);
    AVLnode<T>* rotateRightThenLeft(AVLnode<T>* n);
    AVLnode<T>* copyTree(AVLnode<T>* tree);
    void rebalance(AVLnode<T>* n);
    int height(AVLnode<T>* n);
    void setBalance(AVLnode<T>* n);
    void printBalance(AVLnode<T>* n);
    void reverseLevelOrder(AVLnode<T>* n);
    void printGivenLevel(AVLnode<T>* n, int level);
    unsigned int getfullCount(struct AVLnode<T>* node);
    T sumkeys(AVLnode<T>* root);
    void deleteeven(AVLnode<T>* node);
    void secondLargestUtil(AVLnode<T>* root, int& c);
    void secondLargest(AVLnode<T>* root);
    int size(AVLnode<T>* node);
    bool findPath(AVLnode<T>* root, vector<int>& path, int k);
    T findLCA(AVLnode<T>* root, T n1, T n2);
    void findParent(struct AVLnode<T>* node, T val, T parent);
    void insertToHash(AVLnode<T>* root, unordered_set<int>& s);
    bool checkBSTs(AVLnode<T>* root1, AVLnode<T>* root2);
    T findMedian(struct AVLnode<T>* root);
    int counNodes(struct AVLnode<T>* root);
    void PrintSorted(struct AVLnode<T>* node, int n);
    void inserttrees(AVLnode<T>* a, AVLnode<T>* b, int n);
    bool identicalTrees(AVLnode<T>* a, AVLnode<T>* b);
    bool SymmetricalBBST(struct AVLnode<T>* root1, struct AVLnode<T>* root2);
    void deleteduplicates(struct AVLnode<T>* root1);

};

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
    for (i = h+1; i >= 1; i--)
        printGivenLevel(n, i);
}

template <class T>
void AVLtree<T>::deleteeven(AVLnode<T>* node)
{
    node->left = NULL;
    node->right = NULL;
    node->key = NULL;
}

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
T AVLtree<T>::sumkeys(AVLnode<T>* root)
{
    if (root == NULL)
        return 0;
    return (root->key + sumkeys(root->left) + sumkeys(root->right));
}

template <class T>
unsigned int AVLtree<T>::getfullCount(struct AVLnode<T>* node)
{
    if (!node)
        return 0;
    queue<AVLnode<T>*> q;

    int count = 0;
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
AVLnode<T>* AVLtree<T>::newNode(int key)
{
    AVLnode<T>* temp = new AVLnode<T>(key, NULL);
    temp->key = key;
    temp->right = temp->left = NULL;
    return (temp);
}
template <class T>
AVLnode<T>* AVLtree<T>::copyLeftRightNode(AVLnode<T>* treeNode, unordered_map<AVLnode<T>*, AVLnode<T>*>& mymap)
{
    if (treeNode == NULL)
        return NULL;
    AVLnode<T>* cloneNode = newNode(treeNode->key);
    mymap[treeNode] = cloneNode;
    cloneNode->left = copyLeftRightNode(treeNode->left, mymap);
    cloneNode->right = copyLeftRightNode(treeNode->right, mymap);
    return cloneNode;
}

template <class T>
AVLnode<T>* AVLtree<T>::copyTree(AVLnode<T>* tree)
{
    if (tree == NULL)
        return NULL;
    unordered_map<AVLnode<T>*, AVLnode<T>*> mymap;
    AVLnode<T>* newTree = copyLeftRightNode(tree, mymap);
    return newTree;
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

template <class T>
void AVLtree<T>::secondLargestUtil(AVLnode<T>* root, int& c)
{
    if (root == NULL || c >= 2)
        return;

    secondLargestUtil(root->right, c);

    c++;

    if (c == 2)
    {
        cout << "2nd largest element is "
            << root->key << endl;
        return;
    }

    secondLargestUtil(root->left, c);
}
template <class T>
void AVLtree<T>::secondLargest(AVLnode<T>* root)
{
    int c = 0;

    secondLargestUtil(root, c);
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
    int lh;
    int rh;

    if (root == NULL)
        return 1;

    lh = diff(tree);

    if (abs(lh) <= 1 && isbalanced(tree))
        return 1;

    return 0;
}
template< typename T >
int AVLtree<T>::size(AVLnode<T>* node)
{
    if (node == NULL)
        return 0;
    else
        return(size(node->left) + 1 + size(node->right));
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
        cout << "Element " << el << " is in the tree" << "  ";
    }
    else search(tree->right, el);
}

template< typename T >
void AVLtree<T>::PrintSorted(struct AVLnode<T>* tree, int n)
{
    int t = counNodes(tree);
    
    if (tree == NULL)
        return;
    PrintSorted(tree->left, n);
    cout << tree->key << "  ";
    a<T>.push_back(tree->key);
    PrintSorted(tree->right, n);
    
    if (a<T>.size() == n) {
        cout << endl;
        for (int i = a<T>.size() - 1; i >= 0; i--) {
            cout << a<T>[i] << "  ";
        }
        a<T>.push_back(tree->key);
        return;
    }
}

template< typename T >
int AVLtree<T>::diff(AVLnode<T>* temp)
{
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int b_factor = l_height - r_height;
    return b_factor;
}
template< typename T >
void AVLtree<T>::findParent(struct AVLnode<T>* node, T val, T parent)
{
    if (node == NULL)
        return;

    if (node->key == val) {

        cout << parent;
    }
    else {
        findParent(node->left, val, node->key);
        findParent(node->right, val, node->key);
    }
}


template< typename T >
void AVLtree<T>::insertToHash(AVLnode<T>* root, unordered_set<int>& s)
{
    if (!root)
        return;
    insertToHash(root->left, s);
    s.insert(root->key);
    insertToHash(root->right, s);
}

template< typename T >
bool AVLtree<T>::checkBSTs(AVLnode<T>* root1, AVLnode<T>* root2)
{
    if (!root1 && !root2)
        return true;
    if ((root1 && !root2) || (!root1 && root2))
        return false;

    unordered_set<int> s1, s2;
    insertToHash(root1, s1);
    insertToHash(root2, s2);

    return (s1 == s2);
}
template< typename T >
int AVLtree<T>::counNodes(struct AVLnode<T>* root)
{
    struct AVLnode<T>* current, * pre;

    int count = 0;

    if (root == NULL)
        return count;

    current = root;
    while (current != NULL)
    {
        if (current->left == NULL)
        {
            count++;

            current = current->right;
        }
        else
        {
            pre = current->left;

            while (pre->right != NULL &&
                pre->right != current)
                pre = pre->right;

            if (pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }

            else
            {
                pre->right = NULL;

                count++;
                current = current->right;
            }
        } 
    }

    return count;
}

template< typename T >
bool AVLtree<T>::SymmetricalBBST(struct AVLnode<T>* root1, struct AVLnode<T>* root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 && root2 && root1->key == root2->key)
        return isMirror(root1->left, root2->right)
        && isMirror(root1->right, root2->left);

    return false;
}

template< typename T >
void AVLtree<T>::deleteduplicates(struct AVLnode<T>* root1)
{
    if (root1 == NULL)
        return;
    postorder(root1->left);
    postorder(root1->right);
    dup.push_back();
    dup.erase(unique(dup.begin(), dup.end()), dup.end());
    deleteeven(root1);
    for (int i = 0; i < dup<T>.size(); i++) {
        insert(dup[i]);
    }
}

template< typename T >
T AVLtree<T>::findMedian(struct AVLnode<T>* root)
{
    if (root == NULL)
        return 0;

    int count = counNodes(root);
    int currCount = 0;
    struct AVLnode<T>* current = root, * pre, * prev;

    while (current != NULL)
    {
        if (current->left == NULL)
        {
            prev = current;
            currCount++;

            if (count % 2 != 0 && currCount == (count + 1) / 2)
                return prev->key;

            else if (count % 2 == 0 && currCount == (count / 2) + 1)
                return (prev->key + current->key) / 2;

            prev = current;

            current = current->right;
        }
        else
        {
            pre = current->left;
            while (pre->right != NULL && pre->right != current)
                pre = pre->right;

            if (pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }

            else
            {
                pre->right = NULL;

                prev = pre;

                currCount++;

                if (count % 2 != 0 && currCount == (count + 1) / 2)
                    return current->key;

                else if (count % 2 == 0 && currCount == (count / 2) + 1)
                    return (prev->key + current->key) / 2;

                prev = current;
                current = current->right;

            }
        }
    }
}

template< typename T >
bool AVLtree<T>::findPath(AVLnode<T>* root, vector<int>& path, int k)
{
    if (root == NULL) return false;

    path.push_back(root->key);

    if (root->key == k)
        return true;

    if ((root->left && findPath(root->left, path, k)) ||
        (root->right && findPath(root->right, path, k)))
        return true;

    path.pop_back();
    return false;
}

template< typename T >
T AVLtree<T>::findLCA(AVLnode<T>* root, T n1, T n2)
{
    vector<int> path1, path2;

    if (!findPath(root, path1, n1) || !findPath(root, path2, n2))
        return -1;

    int i;
    for (i = 0; i < path1.size() && i < path2.size(); i++)
        if (path1[i] != path2[i])
            break;
    return path1[i - 1];
}

template< typename T >
bool AVLtree<T>::identicalTrees(AVLnode<T>* a, AVLnode<T>* b)
{
    if (a == NULL && b == NULL)
        return 1;

    if (a != NULL && b != NULL)
    {
        return
            (
                a->key == b->key &&
                identicalTrees(a->left, b->left) &&
                identicalTrees(a->right, b->right)
                );
    }

    return 0;
}


template< typename T >
void AVLtree<T>::inserttrees(AVLnode<T>* A, AVLnode<T>* b, int n)
{
    int t = counNodes(b);

    if (b == NULL)
        return;
    inserttrees(A, b->left, n);
    cout << b->key << "  ";
    un<T>.push_back(b->key);
    inserttrees(A, b->right, n);

    if (un<T>.size() == n) {
        for (int i = un<T>.size() - 1; i >= 0; i--) {
            insert(un<T>[i]);
        }
        un<T>.push_back(b->key);
        return;
    }

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
    cout <<"Height "<<  t.height(t.root);
    cout << endl;
    cout << "Is full " << t.isfull(t.root);
    cout << endl;
    cout << "Diff " << t.diff(t.root);
    cout << endl;

    t.printBalance();
    cout << endl;
    t.getfullCount(t.root);

    //string
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
 
    cout << t.getfullCount(t.root)<<endl;
    cout << t.sumkeys(t.root) << endl;
    
    t.secondLargest(t.root);
    cout << endl;
    cout<<t.size(t.root)<<endl;
    cout << t.findLCA(t.root, 1, 3)<<endl;
    t.findParent(t.root, 1, -100000);
    cout << endl;
    cout << endl;
    int n = t.counNodes(t.root);
    t.PrintSorted(t.root, n);
    cout << endl;
    AVLtree<int> a;
    AVLtree<int> b;
    AVLtree<int> c;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    b.insert(1);
    b.insert(2);
    b.insert(3);
    c.copyTree(a.root);
    a.display(a.root, 1);
    cout << endl << a.identicalTrees(a.root, b.root) << endl;
    b.insert(4);

    a.inserttrees(a.root, b.root, 0);

    cout << a.identicalTrees(a.root, b.root) << endl;

    cout<<a.checkBSTs(a.root, b.root)<<endl;

    cout << a.findMedian(a.root);

    a.deleteeven(a.root);

}
