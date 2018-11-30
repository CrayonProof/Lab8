#include "Node.h"
#include "AVLInterface.h"
#include <iostream>
using namespace std;

class AVL :
    public AVLInterface
{
    public :
    AVL();
    ~AVL();
    Node * getRootNode() const;
    bool add(int data);
    bool findAndRemove(Node * &localRoot, int data);
    bool remove(int data);
    void travClear(Node * node);
    void clear();
    bool balanceTree();
    bool leftRotate(Node * &n);
    bool rightRotate(Node * &n);
    bool isLeftImbalanced(Node * n);
    bool isRightImbalanced(Node * n);
    Node * locateViolater(Node * n);
    bool treeBalanced(Node * n);
	private :
	    Node * rootNode;
	    
};