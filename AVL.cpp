#include "AVL.h"
#include <iostream>
#include "Node.h"
using namespace std;


        AVL::AVL()
        {
            rootNode = NULL;
        }
    	AVL::~AVL()
    	{
    	    clear();
    	}
    	
    	/*
    	* Returns the root node for this tree
    	*
    	* @return the root node for this tree.
    	*/
    	Node * AVL::getRootNode() const
    	{
    	    return rootNode;
    	}
    	
    	/*
    	* Attempts to add the given int to the AVL tree
    	*
    	* @return true if added
    	* @return false if unsuccessful (i.e. the int is already in tree)
    	*/
    	bool AVL::add(int data)
    	{
    	    if (rootNode == NULL)
    	    {
    	        rootNode = new Node(data);
    	        cout << "added node at root wtih data: " << rootNode->data << endl;
    	        balanceTree();
    	        return true;
    	    }
    	    else
    	    {
    	        Node * lookingAt = rootNode;
    	        while (true)
    	        {
    	            if (lookingAt->data == data)
    	            {
    	                return false;
    	            }
    	            else if (lookingAt->data > data)
    	            {
    	                if (lookingAt->leftChild == NULL)
    	                {
    	                    lookingAt->leftChild = new Node(data);
    	                    cout << "added node at left wtih data: " << lookingAt->leftChild->data << endl;
    	                    balanceTree();
    	                    return true;
    	                }
    	                lookingAt = lookingAt->leftChild;
    	            }
    	            else if (lookingAt->data < data)
    	            {
    	                if (lookingAt->rightChild == NULL)
    	                {
    	                    lookingAt->rightChild = new Node(data);
    	                    cout << "added node at right wtih data: " << lookingAt->rightChild->data << endl;
    	                    balanceTree();
    	                    return true;
    	                }
    	                lookingAt = lookingAt->rightChild;
    	            }
    	        }
    	    }
    	}
    
        bool AVL::findAndRemove(Node * &localRoot, int data)
        {
            cout << "call to findAndRemove(" << data << ")" << endl;
            if (localRoot == NULL)
            {
                return false;
            }
            else if (data < localRoot->data)
            {
                cout << "recCall ONE" << endl;
                return findAndRemove(localRoot->leftChild, data);
            }
            else if (data > localRoot->data)
            {
                cout << "recCall TWO" << endl;
                return findAndRemove(localRoot->rightChild, data);
            }
            else if (data == localRoot->data)
            {
                
                if (localRoot->leftChild == NULL && localRoot->rightChild == NULL)
                {
                    cout << "ONE" << endl;
                    Node * toRemove = localRoot;
                    
                    localRoot = NULL;
                    
                    delete toRemove;
                    balanceTree();
                    return true;
                }
                else if (localRoot->rightChild != NULL && localRoot->leftChild == NULL)
                {
                    cout << "TWO" << endl;
                    Node * toRemove = localRoot;
                    
                    localRoot = localRoot->rightChild;
                    
                    delete toRemove;
                    balanceTree();
                    return true;
                }
                else if (localRoot->leftChild != NULL && localRoot->rightChild == NULL)
                {
                    cout << "THREE" << endl;
                    Node * toRemove = localRoot;
                    
                    localRoot = localRoot->leftChild;
                    
                    delete toRemove;
                    balanceTree();
                    return true;
                }
                else if (localRoot->leftChild != NULL && localRoot->rightChild != NULL)
                {
                    if (false) //(localRoot->leftChild->rightChild == NULL)
                    {
                        cout << "FOUR LR NULL: " << data << endl;
                        Node * toRemove = localRoot;
                        
                        localRoot = localRoot->leftChild;
                        
                        delete toRemove;
                        balanceTree();
                        return true;
                    }
                    else
                    {
                        cout << "FOUR INORD PRED: " << data << endl;
                        Node * toRemove = localRoot;
                        Node * inordPred = localRoot->leftChild;
                        
                        while(inordPred->rightChild != NULL)
                        {
                            inordPred = inordPred->rightChild;
                        }
                        
                        localRoot->data = inordPred->data;
                        findAndRemove(localRoot->leftChild, localRoot->data);
                        balanceTree();
                        return true;
                    }
                }
            }
            
        }
    
    	/*
    	* Attempts to remove the given int from the AVL tree
    	*
    	* @return true if successfully removed
    	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
    	*/
    	bool AVL::remove(int data)
    	{
    	    cout << "remove()" << endl;
    	        return findAndRemove(rootNode, data);
    	}
    
        void AVL::travClear(Node * node)
        {
            cout << "travClear" << endl;
            
            if(node->leftChild != NULL)
                travClear(node->leftChild);
            if(node->rightChild != NULL)
                travClear(node->rightChild);
            delete node;
        }
    
    	/*
    	* Removes all nodes from the tree, resulting in an empty tree.
    	*/
    	void AVL::clear()
    	{
    	    cout << "clear()" << endl;
    	    /*
    	    if (rootNode != NULL)
    	    {
    	        travClear(rootNode);
    	        rootNode = NULL;
    	    }
    	    */
    	    
    	    while (rootNode != NULL)
    	    {
    	        remove(rootNode->data);
    	    }
    	}
    	
    	bool AVL::balanceTree()
    	{
    	    
    	    if (treeBalanced(rootNode))
    	    {
    	        return true;
    	    }
    	    else
    	    {
    	        Node * vNode = locateViolater(rootNode);
    	        
    	        if(isLeftImbalanced(vNode))
        	    {
        	        //left-right imbalance
        	        if(isLeftImbalanced(vNode->rightChild))
        	        {
        	            //left rotate on left child
        	            leftRotate(vNode->leftChild);
        	            //right rotate on violating node
        	            rightRotate(vNode);
        	        }
        	        //left-left imbalance or left-equal
        	        else
        	        {
        	            //right rotate on violating node
        	            rightRotate(vNode);
        	        }
        	    }
        	    
        	    else if(isRightImbalanced(vNode))
        	    {
        	        //right-left imbalance
        	        if(isRightImbalanced(vNode->leftChild))
        	        {
        	            //right rotate on right child
        	            rightRotate(vNode->rightChild);
        	            //left rotate on violating node
        	            leftRotate(vNode);
        	        }
        	        //right-right imbalance or right-equal
        	        else
        	        {
        	            //left rotate on violating node
        	            leftRotate(vNode);
        	        }
        	    }
    	    }
    	    
    	    
    	}
    	
    	bool AVL::leftRotate(Node * &n)
    	{
    	    Node * oldNode = n;
    	    Node * newNode = oldNode->rightChild;
    	    Node * parentPtr = newNode;
    	    oldNode->rightChild = newNode->leftChild;
    	    newNode->leftChild = oldNode;
    	}
        bool AVL::rightRotate(Node * &n)
        {
            Node * oldNode = n;
    	    Node * newNode = oldNode->leftChild;
    	    Node * parentPtr = newNode;
    	    oldNode->leftChild = newNode->rightChild;
    	    newNode->rightChild = oldNode;
        }
        bool AVL::isLeftImbalanced(Node * n)
        {
            int lHeight = -1;
            int rHeight = -1;
            
            if (n == NULL)
                return true;
            if (n->getHeight() == 0)
            {
                return false;
            }
            if (n->leftChild != NULL)
            {
                lHeight = n->leftChild->getHeight();
            }
            if (n->rightChild != NULL)
            {
                rHeight = n->rightChild->getHeight();
            }
            
            if(lHeight - rHeight > 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool AVL::isRightImbalanced(Node * n)
        {
            int lHeight = -1;
            int rHeight = -1;
            
            if (n == NULL)
                return true;
            if (n->getHeight() == 0)
            {
                return false;
            }
            if (n->leftChild != NULL)
            {
                lHeight = n->leftChild->getHeight();
            }
            if (n->rightChild != NULL)
            {
                rHeight = n->rightChild->getHeight();
            }
            if(rHeight - lHeight > 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
        bool AVL::treeBalanced(Node * n)
        {
            if (isLeftImbalanced(n) || isRightImbalanced(n))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        
        //should only be called when tree is known to be imballanced
        Node * AVL::locateViolater(Node * n)
        {
            if (treeBalanced(n) || n == NULL) 
            {
                return n;
            }
            else
            {
                if (isLeftImbalanced(n))
                {
                    if (n->leftChild == NULL)
                    {
                        return n;
                    }
                    else
                    {
                       locateViolater(n->leftChild); 
                    }
                }
                else if (isRightImbalanced(n))
                {
                    if (n->rightChild == NULL)
                    {
                        return n;
                    }
                    else
                    {
                        locateViolater(n->rightChild);
                    }
                }
            }
        }