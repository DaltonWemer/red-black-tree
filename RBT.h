// Node structure in Red-Black Tree
struct Node {
    int key;
    Node *p; 
    Node *left; 
    Node *right; 
    char color; 
};

// Pointer to a node to reduce confusion about passing nodes around
typedef Node *nodePtr;

class RBT {
    private:
        nodePtr root;
        nodePtr TNIL;

    public:
        // nullptr was introdiced to c++ in version 11, so this line will not compile in any version
        // under that.
        RBT() {
            TNIL = new Node;
            TNIL->color = 'B';
            TNIL->left = nullptr;
            TNIL->right = nullptr;
            root = TNIL;
        }

        // Primary operations to be carried out by the program
        void output(nodePtr node, int indent = 0);
        nodePtr search(nodePtr T, int key);
        void insert(int key);
        bool deleteKey(int key);
 
        // Functions needed to complete the primary operations
        static nodePtr new_node(char color, int key, nodePtr left, nodePtr right, nodePtr p);
        void transplant(nodePtr u, nodePtr v);
        nodePtr getMin(nodePtr x);
        void deleteFixup(nodePtr x);
        void insertFixup(nodePtr z);
        void clear(nodePtr T);
        nodePtr getRoot();
        void leftRotate(nodePtr x);
        void rightRotate(nodePtr y);
        void setRoot(nodePtr T);
        nodePtr getTNIL();
};

