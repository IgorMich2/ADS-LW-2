
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
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
    AVLnode<T>* cloneTree(AVLnode<T>* tree);
    void rebalance(AVLnode<T>* n);
    int height(AVLnode<T>* n);
    void setBalance(AVLnode<T>* n);
    void printBalance(AVLnode<T>* n);
    void reverseLevelOrder(AVLnode<T>* n);
    void printGivenLevel(AVLnode<T>* n, int level);
    unsigned int getfullCount(struct AVLnode<T>* node);
    int sumkeys(AVLnode<T>* root);
    void deleteeven(AVLnode<T>* node);
    void secondLargestUtil(AVLnode<T>* root, int& c);
    void secondLargest(AVLnode<T>* root);
    int size(AVLnode<T>* node);
    bool findPath(AVLnode<T>* root, vector<int>& path, int k);
    T findLCA(AVLnode<T>* root, T n1, T n2);
    void findParent(struct AVLnode<T>* node, T val, T parent);
    void insertToHash(AVLnode<T>* root, unordered_set<int>& s);
    bool checkBSTs(AVLnode<T>* root1, AVLnode<T>* root2);
    int findMedian(struct AVLnode<T>* root);
    int counNodes(struct AVLnode<T>* root);

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
    node->left = NULL;
    node->right = NULL;
    node->key = NULL;
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
int AVLtree<T>::sumkeys(AVLnode<T>* root)
{
    if (root == NULL)
        return 0;
    return (root->key + sumkeys(root->left) + sumkeys(root->right));
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
AVLnode<T>* AVLtree<T>::cloneTree(AVLnode<T>* tree)
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

template <class T>
void AVLtree<T>::secondLargestUtil(AVLnode<T>* root, int& c)
{
    // Base cases, the second condition is important to
    // avoid unnecessary recursive calls
    if (root == NULL || c >= 2)
        return;

    // Follow reverse inorder traversal so that the
    // largest element is visited first
    secondLargestUtil(root->right, c);

    // Increment count of visited nodes
    c++;

    // If c becomes k now, then this is the 2nd largest
    if (c == 2)
    {
        cout << "2nd largest element is "
            << root->key << endl;
        return;
    }

    // Recur for left subtree
    secondLargestUtil(root->left, c);
}
template <class T>
void AVLtree<T>::secondLargest(AVLnode<T>* root)
{
    // Initialize count of nodes visited as 0
    int c = 0;

    // Note that c is passed by reference
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
template< typename T >
void AVLtree<T>::findParent(struct AVLnode<T>* node, T val, T parent)
{
    if (node == NULL)
        return;

    // If current node is the required node
    if (node->key == val) {

        // Print its parent
        cout << parent;
    }
    else {

        // Recursive calls for the children
        // of the current node
        // Current node is now the new parent
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

// function to check if the two BSTs contain
// same set  of elements
template< typename T >
bool AVLtree<T>::checkBSTs(AVLnode<T>* root1, AVLnode<T>* root2)
{
    // Base cases 
    if (!root1 && !root2)
        return true;
    if ((root1 && !root2) || (!root1 && root2))
        return false;

    // Create two hash sets and store 
    // elements both BSTs in them.
    unordered_set<int> s1, s2;
    insertToHash(root1, s1);
    insertToHash(root2, s2);

    // Return true if both hash sets 
    // contain same elements.
    return (s1 == s2);
}
template< typename T >
int AVLtree<T>::counNodes(struct AVLnode<T>* root)
{
    struct AVLnode<T>* current, * pre;

    // Initialise count of nodes as 0
    int count = 0;

    if (root == NULL)
        return count;

    current = root;
    while (current != NULL)
    {
        if (current->left == NULL)
        {
            // Count node if its left is NULL
            count++;

            // Move to its right
            current = current->right;
        }
        else
        {
            /* Find the inorder predecessor of current */
            pre = current->left;

            while (pre->right != NULL &&
                pre->right != current)
                pre = pre->right;

            /* Make current as right child of its
               inorder predecessor */
            if (pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }

            /* Revert the changes made in if part to
               restore the original tree i.e., fix
               the right child of predecssor */
            else
            {
                pre->right = NULL;

                // Increment count if the current
                // node is to be visited
                count++;
                current = current->right;
            } /* End of if condition pre->right == NULL */
        } /* End of if condition current->left == NULL*/
    } /* End of while */

    return count;
}

/* Function to find median in O(n) time and O(1) space
   using Morris Inorder traversal*/
template< typename T >
int AVLtree<T>::findMedian(struct AVLnode<T>* root)
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
            // count current node
            currCount++;

            // check if current node is the median
            // Odd case
            if (count % 2 != 0 && currCount == (count + 1) / 2)
                return prev->key;

            // Even case
            else if (count % 2 == 0 && currCount == (count / 2) + 1)
                return (prev->key + current->key) / 2;

            // Update prev for even no. of nodes
            prev = current;

            //Move to the right
            current = current->right;
        }
        else
        {
            /* Find the inorder predecessor of current */
            pre = current->left;
            while (pre->right != NULL && pre->right != current)
                pre = pre->right;

            /* Make current as right child of its inorder predecessor */
            if (pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }

            /* Revert the changes made in if part to restore the original
              tree i.e., fix the right child of predecssor */
            else
            {
                pre->right = NULL;

                prev = pre;

                // Count current node
                currCount++;

                // Check if the current node is the median
                if (count % 2 != 0 && currCount == (count + 1) / 2)
                    return current->key;

                else if (count % 2 == 0 && currCount == (count / 2) + 1)
                    return (prev->key + current->key) / 2;

                // update prev node for the case of even
                // no. of nodes
                prev = current;
                current = current->right;

            } /* End of if condition pre->right == NULL */
        } /* End of if condition current->left == NULL*/
    } /* End of while */
}




// Utility function creates a new binary tree node with given key


// Finds the path from root node to given root of the tree, Stores the
// path in a vector path[], returns true if path exists otherwise false
template< typename T >
bool AVLtree<T>::findPath(AVLnode<T>* root, vector<int>& path, int k)
{
    // base case
    if (root == NULL) return false;

    // Store this node in path vector. The node will be removed if
    // not in path from root to k
    path.push_back(root->key);

    // See if the k is same as root's key
    if (root->key == k)
        return true;

    // Check if k is found in left or right sub-tree
    if ((root->left && findPath(root->left, path, k)) ||
        (root->right && findPath(root->right, path, k)))
        return true;

    // If not present in subtree rooted with root, remove root from
    // path[] and return false
    path.pop_back();
    return false;
}

// Returns LCA if node n1, n2 are present in the given binary tree,
// otherwise return -1
template< typename T >
T AVLtree<T>::findLCA(AVLnode<T>* root, T n1, T n2)
{
    // to store paths to n1 and n2 from the root
    vector<int> path1, path2;

    // Find paths from root to n1 and root to n1. If either n1 or n2
    // is not present, return -1
    if (!findPath(root, path1, n1) || !findPath(root, path2, n2))
        return -1;

    /* Compare the paths to get the first different value */
    int i;
    for (i = 0; i < path1.size() && i < path2.size(); i++)
        if (path1[i] != path2[i])
            break;
    return path1[i - 1];
}




template< typename T >
bool identicalTrees(AVLnode<T>* a, AVLnode<T>* b)
{
    if (a == NULL && b == NULL)
        return 1;

    /* 2. both non-empty -> compare them */
    if (a != NULL && b != NULL)
    {
        return
            (
                a->key == b->key &&
                identicalTrees(a->left, b->left) &&
                identicalTrees(a->right, b->right)
                );
    }

    /* 3. one empty, one not -> false */
    return 0;
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

   /* AVLtree<string> s;


    s.insert("sa");
    s.insert("ab");
    s.insert("cd");

    s.printBalance();
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    s.display(s.root, 1);*/
 
    cout << t.getfullCount(t.root)<<endl;
    cout << t.sumkeys(t.root) << endl;
    
    t.secondLargest(t.root);
    cout << endl;
    cout<<t.size(t.root)<<endl;
    cout << t.findLCA(t.root, 1, 3)<<endl;
    t.findParent(t.root, 1, -100000);



    AVLtree<int> a;
    AVLtree<int> b;
    AVLtree<int> c;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    b.insert(1);
    b.insert(2);
    b.insert(3);

    cout << endl << identicalTrees(a.root, b.root) << endl;
    b.insert(4);
    cout << identicalTrees(a.root, b.root) << endl;

    cout<<a.checkBSTs(a.root, b.root)<<endl;

    cout << a.findMedian(a.root);
    
    a.deleteeven(a.root);

}
