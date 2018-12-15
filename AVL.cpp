#include "AVL.h"
#include <iostream>
#include <cmath>
#include "Node.h"
using namespace std;


        AVL::AVL()
        {
            rootNode = NULL;
        }
    	AVL::~AVL()
    	{
    	    clear();
    	    rootNode = NULL;
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
                    
                    delete toRemove;
                    localRoot = NULL;
                    balanceTree();
                    return true;
                }
                else if (localRoot->rightChild != NULL && localRoot->leftChild == NULL)
                {
                    cout << "TWO" << endl;
                    Node * toRemove = localRoot;
                    
                    localRoot = localRoot->rightChild;
                    Node * toNullify = toRemove;
                    
                    delete toRemove;
                    toNullify = NULL;
                    balanceTree();
                    return true;
                }
                else if (localRoot->leftChild != NULL && localRoot->rightChild == NULL)
                {
                    cout << "THREE" << endl;
                    Node * toRemove = localRoot;
                    
                    localRoot = localRoot->leftChild;
                    Node * toNullify = toRemove;
                    
                    delete toRemove;
                    toNullify = NULL;
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
                        Node * toNullify = toRemove;
                        
                        delete toRemove;
                        toNullify = NULL;
                        
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
            else if(node->rightChild != NULL)
                travClear(node->rightChild);
            node = NULL;
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
    	    rBalance(rootNode);
    	}
    	
    	bool AVL::rBalance(Node * &n)
    	{
    	    int rH = -1;
    	    int lH = -1;
    	    
    	    cout << "rBalance(";
    	    if (n == NULL)
    	    {
    	        cout << ")" << endl;
    	        return true;
    	    }
    	    else
    	    {
    	        if (n->leftChild != NULL)
        	    {
        	        lH = n->leftChild->getHeight();
        	    }
        	    if (n->rightChild != NULL)
        	    {
        	        rH = n->rightChild->getHeight();
        	    }
    	        
    	        cout << n->getData() << ")" << endl;
    	        cout << n->getData() << " -- lH: " << lH << ", rH: " << rH << endl;
    	        
    	        if (n->leftChild != NULL)
        	    {
        	        rBalance(n->leftChild);
        	    }
        	    if (n->rightChild != NULL)
        	    {
        	        rBalance(n->rightChild);
        	    }
    	    
    	    }
    	    if (n->rightChild == NULL && n->leftChild == NULL)
    	    {
    	     return true;   
    	    }
    	    if(bal(n) > 1)
    	    {
    	        //left
    	        if(bal(n->leftChild) >=0)
    	        {
    	            //left or equal
    	            cout << "LL" << endl;
    	            rightRotate(n);
    	        }
    	        else if (bal(n->leftChild) < 0)
    	        {
    	            //right
    	            cout << "LR" << endl;
    	            leftRotate(n->leftChild);
    	            rightRotate(n);
    	        }
    	    }
    	    else if(bal(n) < -1)
    	    {
    	        //right
    	        if(bal(n->rightChild) <=0)
    	        {
    	            //right or equal
    	            cout << "RR" << endl;
    	            leftRotate(n);
    	        }
    	        else if (bal(n->rightChild) > 0)
    	        {
    	            //left
    	            cout << "RL" << endl;
    	            rightRotate(n->rightChild);
    	            leftRotate(n);
    	        }
    	    }
    	    else
    	    {
        	    if (n->leftChild != NULL)
        	    {
        	        //rBalance(n->leftChild);
        	    }
        	    else
        	    {
        	        //cout << n->getData() << "'s left child was null" << endl;
        	    }
        	    if (n->rightChild != NULL)
        	    {
        	        //rBalance(n->rightChild);
        	    }
        	    else
        	    {
        	        //cout << n->getData() << "'s right child was null" << endl;
        	    }
        	    return true;
    	    }
    	}
    	
    	int AVL::bal (Node * n)
    	{
    	    int rH = -1;
    	    int lH = -1;
    	    
    	    if (n == NULL)
    	    {
    	        return 0;
    	    }
    	    
    	    if (n->leftChild != NULL)
    	    {
    	        lH = n->leftChild->getHeight();
    	    }
    	    if (n->rightChild != NULL)
    	    {
    	        rH = n->rightChild->getHeight();
    	    }
    	    //cout << n->getData() << " -- lH: " << lH << ", rH: " << rH << endl;
    	    return (lH - rH);
    	}
    	
    	int AVL::wholeTreeBalanced(Node * n, int state)
    	{
    	    
    	}
    	
    	void AVL::chooseRotation(Node * &vNode)
    	{
    	   
    	}
    	
    	bool AVL::leftRotate(Node * &n)
    	{
    	    cout << "leftRotate(" << n->data << ")" << endl;
    	    
    	    Node * newLocalRoot = n->rightChild;
    	    Node * oldLocalRoot = n;
    	    Node * newLocalRootLeft = newLocalRoot->leftChild;
    	    n = newLocalRoot;
    	    oldLocalRoot->rightChild = newLocalRootLeft;
    	    n->leftChild = oldLocalRoot;
    	    
    	}
        bool AVL::rightRotate(Node * &n)
        {
            cout << "rightRotate(" << n->data << ")" << endl;
    	    
    	    Node * newLocalRoot = n->leftChild;
    	    Node * oldLocalRoot = n;
    	    Node * newLocalRootRight = newLocalRoot->rightChild;
    	    n = newLocalRoot;
    	    oldLocalRoot->leftChild = newLocalRootRight;
    	    n->rightChild = oldLocalRoot;
        }
        bool AVL::isLeftImbalanced(Node * n)
        {
            
        }
        bool AVL::isRightImbalanced(Node * n)
        {
            
        }
        
        int AVL::heavySide(Node * n)
        {
            
        }
        
        bool AVL::treeBalanced(Node * n)
        {
            
        }
        
        //should only be called when tree is known to be imballanced
        Node * AVL::locateViolater(Node * &n)
        {
            
        }