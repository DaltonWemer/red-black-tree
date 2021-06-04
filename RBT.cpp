#include "RBT.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Returns a new node with the parameters passed in by the user. Needed to be able to insert
// a new node into the Red/Black Tree
nodePtr RBT::new_node(char color, int key, nodePtr left, nodePtr right, nodePtr p){
    // Create a tree node
    nodePtr node = new Node;
    node -> color = color;
    node -> key = key;
    node -> left = left;
    node -> right = right;
    node -> p = p;

    return node;
}

// We can insert into a Red/Black tree in O(log n) time. We first perform a normal
// Binary Search Tree Insertion. Replace all instances of TNil with T.Nil
// we then set the z.left and z.right to T.Nil. This maintains proper tree structure. It is
// then time to assign a color to our new node (z). To ensure that the insertion
// does not break any of the rules of the Red and Black Tree, we must call insertFixup(newNode).
void RBT::insert(int key){
    // Create new node to be inserted into our Red and Black Tree
    nodePtr z = new_node('B', key, TNIL, TNIL, TNIL);
    // Pointers to be overridden
    nodePtr y = TNIL;
    nodePtr x = root;
    while(x != TNIL){
        y = x;
        if(z -> key < x -> key){
            x = x -> left;
        }else{
            x = x -> right;
        }
    }
    z -> p = y;
    if(y == TNIL){
        root = z;
    }else if(z -> key < y -> key){
        y -> left = z;
    }else{
        y -> right = z;
    }
    z -> left = TNIL;
    z -> right = TNIL;
    z -> color = 'R';
    insertFixup(z);
}

// Used to rotate a tree to the left if any illegal insertion or
// deletion is attempted
void RBT::leftRotate(nodePtr x)
{
    nodePtr y = x -> right; 
    x -> right = y -> left;
    if(y -> left != TNIL){
        y -> left -> p = x;
    }
    y -> p = x -> p;
    if(x -> p == TNIL){
        root = y;
    }else if(x == x -> p -> left){
        x->p->left = y;
    }else{
        x->p->right = y;
    }
    y -> left = x;
    x -> p = y;
}

// Used to rotate a tree to the right if any illegal insertion 
// or deletion is attempted
void RBT::rightRotate(nodePtr y)
{
    nodePtr x = y -> left;
    y -> left = x -> right;
    if(x -> right != TNIL){
        x -> right -> p = y;
    }
    x -> p = y -> p;
    if(y -> p == TNIL){
        root = x;
    }else if(y == y -> p -> right){
        y -> p -> right = x;
    }else{
        y -> p -> left = x;
    }
    x -> right = y;
    y -> p = x;
}

// Prints the red/black tree in a way that is easy to read from the 
// console. We took the simpler approach of rotating the rbt 90 degrees.
// Operation is O(n) just like the BST print. The operation is actually
// identical to that of BST print except for the fact that we need to print
// NILL if a new node has not been inserted at the position.
void RBT::output(nodePtr node, int indent)
{   
    // Because our tree is shifted 90 degrees, we want to print all of the nodes
    // on the right side of the tree first
    if(node -> right != nullptr)
    {
        output(node -> right, indent+5);
    }
    // Add the indention to the output
    if(indent!=0)
    {
        std::cout << std::setw(indent);
    }

    // Print out the TNIL for tree balancing if no node exists yet
    node == TNIL ?  std::cout << "nil" << "\n" : std::cout << node -> key << node -> color << "\n"; 

    // Finally, print all of the nodes on the left side of the tree
    if(node -> left != NULL)
    {
        output( node -> left, indent + 5);
    }
}


// Similar to the transplant you would do on a BST except we must
// keep track of the color. TH
void RBT::transplant(nodePtr u, nodePtr v)
{
    if(u -> p == TNIL){
        root = v;
    }else if(u == u -> p -> left){
        u -> p -> left = v;
    }else{
        u -> p -> right = v;
    }
    v -> p = u -> p;
}

// Perform a search on the red and black tree and delete the node
// corresponding to the key that was passed in. This procedure is much more 
// complicated than the insert.
bool RBT::deleteKey(int key)
{
    nodePtr z = search(root, key);
    if(z != TNIL)
    {
        nodePtr y = z; 
        char y_org_color = y->color;
        nodePtr x;
        if(z -> left == TNIL){
            x = z -> right;
            transplant(z, z -> right);
        }else if(z -> right == TNIL){
            x = z -> left;
            transplant(z, z -> left);
        }else{
            y = getMin(z -> right);
            y_org_color = y -> color;
            x = y -> right;
            if(y -> p == z){
                x -> p = y;
            }else{
                transplant(y, y -> right);
                y -> right = z -> right;
                y -> right->p = y;
            }
            transplant(z, y);
            y -> left = z -> left;
            y -> left -> p = y;
            y -> color = z -> color;
        }
        if(y_org_color == 'B'){
            deleteFixup(x);
        }
        return true;
    }else{
        return false;
    }
}

// Get the nill child 
nodePtr RBT::getTNIL()
{
    return this->TNIL;
}

// Sets the root of the RBT tree to the node pointer passed in
void RBT::setRoot(nodePtr T)
{
    this->root = T;
}

// Return the root node of the current instance of RBT
nodePtr RBT::getRoot()
{
    return this->root;
}

// Removes the node from memory to prevent a memory leak
void RBT::clear(nodePtr t) 
{
    if(t != TNIL){
        clear(t->left);
        clear(t->right);
        delete t;
    }
}

// Searching the RBT is a O(log n) operation
nodePtr RBT::search(nodePtr T, int key)
{
    // Go throught the tree in pre-order and determine weather or not the key is
    // present. If the key is present, return the node
    if(T == TNIL){
        return T;
    }else if(key < T->key){
        return search(T -> left, key);
    }else if(key > T -> key) {
        return search(T -> right, key);
    }else{
        return T;
    }
}

// Return the lowest key stored in the red black tree
nodePtr RBT::getMin(nodePtr x)
{
    while(x->left != TNIL){
        x = x->left;
    }
    return x;
}

// Reassign colors after insertion to rebalance the tree
void RBT::insertFixup(nodePtr z)
{
    while(z != root && z -> p -> color == 'R'){
        if(z -> p == z-> p-> p -> left){
            nodePtr y = z -> p -> p -> right; 
            if(y -> color == 'R'){
                z -> p -> color = 'B';
                y-> color = 'B';
                z -> p -> p-> color = 'R';
                z = z -> p -> p;
            }else{
                if(z == z -> p -> right){
                    z = z -> p;
                    leftRotate(z);
                }
                z -> p -> color = 'B';
                z -> p -> p -> color = 'R';
                rightRotate(z -> p -> p);
            }
        }else{
            nodePtr y = z -> p -> p -> left;
            if(y -> color == 'R'){
                z -> p -> color = 'B';
                y -> color = 'B';
                z -> p -> p -> color = 'R';
                z = z -> p -> p;
            }else{
                if(z == z -> p -> left){
                    z = z -> p;
                    rightRotate(z);
                }
                z -> p -> color = 'B';
                z -> p -> p -> color = 'R';
                leftRotate(z -> p -> p);
            }
        }
    }
    root -> color = 'B';
}

// Reassign colors after deletion to rebalance the tree
void RBT::deleteFixup(nodePtr x)
{
    while(x != root && x -> color == 'B'){
        if(x == x -> p -> left){
            nodePtr w = x -> p -> right;
            if(w -> color == 'R'){
                w -> color = 'B';
                x -> p -> color = 'R';
                leftRotate(x -> p);
                w = x -> p -> right;
            }
            if(w -> left -> color == 'B' && w -> right -> color == 'B'){
                w -> color = 'R';
                x = x -> p;
            }else{
                if(w -> right -> color == 'B'){
                    w -> left -> color = 'B';
                    w -> color = 'R';
                    rightRotate(w);
                    w = x -> p -> right;
                }
                w -> color = x -> p -> color;
                x -> p -> color = 'B';
                w -> right -> color = 'B';
                leftRotate(x -> p);
                x = root;
            }
        }else{
            nodePtr w = x -> p -> left;
            if (w -> color == 'R'){
                w -> color = 'B';
                x -> p -> color = 'R';
                rightRotate(x -> p);
                w = x -> p -> left;
            }
            if(w -> right -> color == 'B' && w -> left -> color == 'B'){
                w -> color = 'R';
                x = x -> p;
            }else{
                if(w -> left -> color == 'B'){
                    w -> right -> color = 'B';
                    w -> color = 'R';
                    leftRotate(w);
                    w = x -> p -> left;
                }
                w -> color = x -> p -> color;
                x -> p -> color = 'B';
                w -> left -> color = 'B';
                rightRotate(x -> p);
                x = root;
            }
        }
    }
    x -> color = 'B';
}

