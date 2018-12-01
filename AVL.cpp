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
    	    cout << "balanceTree(" << ")" << endl;
    	    if (treeBalanced(rootNode))
    	    {
    	        return true;
    	    }
    	    else
    	    {
    	        locateViolater(rootNode);
    	        
    	        
    	    }
    	    
    	    
    	}
    	
    	void AVL::chooseRotation(Node * &vNode)
    	{
    	    if(heavySide(vNode) == 1)
    	        {
    	            //right-right
    	            if(heavySide(vNode->rightChild) == 1)
    	            {
    	                leftRotate(vNode);
    	                cout << "rootData: " << rootNode->getData() << endl;
    	            }
    	            //right-left
    	            else if(heavySide(vNode->rightChild) == -1)
    	            {
    	                rightRotate(vNode->rightChild);
    	                leftRotate(vNode);
    	            }
    	            //right-equals
    	            else
    	            {
    	                leftRotate(vNode);
    	            }
    	        }
    	        else if(heavySide(vNode) == -1)
    	        {
    	            //left-left
    	            if(heavySide(vNode->leftChild) == -1)
    	            {
    	               rightRotate(vNode); 
    	               cout << "rootData: " << rootNode->getData() << endl;
    	            }
    	            //left-right
    	            else if (heavySide(vNode->leftChild) == 1)
    	            {
    	                leftRotate(vNode->leftChild);
    	                rightRotate(vNode);
    	            }
    	            //left-equals
    	            else
    	            {
    	                rightRotate(vNode);
    	            }
    	        }
    	}
    	
    	bool AVL::leftRotate(Node * &n)
    	{
    	    cout << "leftRotate(" << n->data << ")" << endl;
    	    /*
    	    Node * oldNode = n;
    	    Node * newNode = oldNode->rightChild;
    	    Node * parentPtr = newNode;
    	    oldNode->rightChild = newNode->leftChild;
    	    newNode->leftChild = oldNode;
    	    */
    	    //cout << "lRoot Right Child: " << n->rightChild->data << endl;
    	    Node * newLocalRoot = n->rightChild;
    	    Node * oldLocalRoot = n;
    	    Node * newLocalRootLeft = newLocalRoot->leftChild;
    	    n = newLocalRoot;
    	    oldLocalRoot->rightChild = newLocalRootLeft;
    	    n->leftChild = oldLocalRoot;
    	    
    	    //cout << "localRoot: " << n->getData() << endl;
    	    //cout << "localRootLeftChild: " << n->leftChild->getData() << endl;
    	    //cout << "localRootLeftChildsRightChild: " << n->leftChild->rightChild->getData() << endl;
    	    
    	}
        bool AVL::rightRotate(Node * &n)
        {
            cout << "rightRotate(" << ")" << endl;
            
            /*
            Node * oldNode = n;
    	    Node * newNode = oldNode->leftChild;
    	    Node * parentPtr = newNode;
    	    oldNode->leftChild = newNode->rightChild;
    	    newNode->rightChild = oldNode;
    	    */
    	    
    	    Node * oldLocalRoot = n;
    	    Node * newLocalRoot = oldLocalRoot->leftChild;
    	    Node * newLocalRootRight = newLocalRoot->rightChild;
    	    n = newLocalRoot;
    	    oldLocalRoot->leftChild = newLocalRootRight;
    	    n->rightChild = oldLocalRoot;
        }
        bool AVL::isLeftImbalanced(Node * n)
        {
            cout << "isLeftImbalanced(" << ")";
            int lHeight = -1;
            int rHeight = -1;
            
            if (n == NULL)
                return false;
            if (n->getHeight() == 0)
            {
                cout << " returned false" << endl;
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
                cout << " returned true" << endl;
                return true;
            }
            else
            {
                cout << " returned false" << endl;
                return false;
            }
        }
        bool AVL::isRightImbalanced(Node * n)
        {
            cout << "isRightImbalanced(" << ")";
            int lHeight = -1;
            int rHeight = -1;
            
            if (n == NULL)
                return false;
            if (n->getHeight() == 0)
            {
                cout << " returned false" << endl;
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
                cout << " returned true" << endl;
                return true;
            }
            else
            {
                cout << " returned false" << endl;
                return false;
            }
        }
        
        int AVL::heavySide(Node * n)
        {
            if (n->getRightHeight() > n->getLeftHeight())
                return 1;
            else if (n->getLeftHeight() > n->getRightHeight())
                return -1;
            else
                return 0;
        }
        
        bool AVL::treeBalanced(Node * n)
        {
            cout << "call to treeBalanced(" << ")" << endl;
            cout << "treeLeftHeight: " << n->getLeftHeight() << endl;
            cout << "treeRightHeight: " << n->getRightHeight() << endl;
            if(abs(n->getLeftHeight() - n->getRightHeight()) <= 1)
            {
                cout << "treeBalanced returned true" << endl;
                return true;
            }
            else
            {
                cout << "treeBalanced returned false" << endl;
                return false;
            }
        }
        
        //should only be called when tree is known to be imballanced
        Node * AVL::locateViolater(Node * &n)
        {
            cout << "locateViolater(" << ")" << endl;
            /*
            if (treeBalanced(n) || n == NULL) 
            {
                cout << "locateViolater returned node with data: " << n->getData() << endl;
                return n;
            }
            
            else
            {
                if (isLeftImbalanced(n))
                {
                    if (n->leftChild == NULL)
                    {
                        cout << "locateViolater returned node with data: " << n->getData() << endl;
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
                        cout << "locateViolater returned node with data: " << n->getData() << endl;
                        return n;
                    }
                    else
                    {
                        locateViolater(n->rightChild);
                    }
                }
            }
            */
            if (!treeBalanced(n))
            {
                bool rightChildIsBalanced = true;
                if (n->rightChild != NULL)
                {
                    rightChildIsBalanced = treeBalanced(n->rightChild);
                }
                bool leftChildIsBalanced = true;
                if (n->leftChild != NULL)
                {
                    leftChildIsBalanced = treeBalanced(n->leftChild);
                }
                if(rightChildIsBalanced)
                {
                    if(leftChildIsBalanced)
                    {
                        cout << "locateViolater returned node with data: " << n->getData() << endl;
                        chooseRotation(n);
                        return n;
                    }
                    else
                    {
                        return locateViolater(n->leftChild);
                    }
                }
                else
                {
                    return locateViolater(n->rightChild);
                }
            }
        }