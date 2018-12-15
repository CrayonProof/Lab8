#include "Node.h"
#include <iostream>
using namespace std;

        Node::Node()
        {
            parent = NULL;
            data = -314159;
            leftChild = NULL;
            rightChild = NULL;
        }
        Node::Node(int data, Node * p) 
        {
            //cout << "new node created with data = " << data << " and no children" << endl;
            this->data = data;
            parent = p;
            leftChild = NULL;
            rightChild = NULL;
        }
        Node::Node(int data) 
        {
            //cout << "new node created with data = " << data << " and no children" << endl;
            this->data = data;
            parent = NULL;
            leftChild = NULL;
            rightChild = NULL;
        }
    	Node::~Node()
    	{
    	    //delete leftChild;
    	    //delete rightChild;
    	    //leftChild = NULL;
    	    //rightChild = NULL;
    	}
    
        /*
    	* Returns the data that is stored in this node
    	*
    	* @return the data that is stored in this node.
    	*/
    	int Node::getData() const
    	{
    	    return data;
    	}

        /*
    	* Returns the left child of this node or null if it doesn't have one.
    	*
    	* @return the left child of this node or null if it doesn't have one.
    	*/
    	Node * Node::getLeftChild() const
    	{
    	    return leftChild;
    	}

        /*
    	* Returns the right child of this node or null if it doesn't have one.
    	*
    	* @return the right child of this node or null if it doesn't have one.
    	*/
    	Node * Node::getRightChild() const
    	{
    	    return rightChild;
    	}
    	
    	bool Node::setData(int data)
    	{
    	    this->data = data;
    	    return true;
    	}
    	
    	bool Node::setLeftChild(Node * newLeftChild)
    	{
    	    leftChild = newLeftChild;
    	    return true;
    	}
    	
    	bool Node::setRightChild(Node * newRightChild)
    	{
    	    rightChild = newRightChild;
    	    return true;
    	}
    	
    	int Node::getHeight()
    	{
    	    //cout << "preDATA: " << this->data << endl;
    	    int lHeight = 0;
    	    if (this->leftChild !=NULL)
    	    {
    	        lHeight += this->leftChild->getHeight() + 1;
    	    }
    	    
    	    int rHeight = 0;
    	    if (this->rightChild !=NULL)
    	    {
    	        rHeight += this->rightChild->getHeight() + 1;
    	    }
    	    
    	    if (this->leftChild == NULL && this->rightChild == NULL)
    	    {
    	        return 0;
    	    }
    	    else
    	    {
    	        if (rHeight > lHeight)
    	        {
    	           return rHeight; 
    	        }
    	        else
    	        {
    	            return lHeight;
    	        }
    	    }
    	    
    	}
    	int Node::getLeftHeight()
    	{
    	    if (this->rightChild == 0)
    	        return 0;
    	    if (this->leftChild == NULL)
    	        return 0;
    	    int lHeight = 1;
    	    Node * lookingAt = this->leftChild;
    	    while (lookingAt->leftChild !=NULL)
    	    {
    	        lookingAt = lookingAt->leftChild;
    	        lHeight += 1;
    	    }
    	    
    	    int rHeight = 1;
    	    lookingAt = this->leftChild;
    	    while (lookingAt->rightChild !=NULL)
    	    {
    	        lookingAt = lookingAt->rightChild;
    	        rHeight += 1;
    	    }
    	    //cout << "postDATA: " << this->data << endl;
    	    if (lHeight > rHeight)
    	    {
    	        return lHeight;
    	    }
    	    else
    	    {
    	        return rHeight;
    	    }
    	}
    	int Node::getRightHeight()
    	{
    	    if (this->rightChild == 0)
    	        return 0;
    	    if (this->rightChild == NULL)
    	        return 0;
    	    int lHeight = 1;
    	    Node * lookingAt = this->rightChild;
    	    while (lookingAt->leftChild !=NULL)
    	    {
    	        lookingAt = lookingAt->leftChild;
    	        lHeight += 1;
    	    }
    	    
    	    int rHeight = 1;
    	    lookingAt = this->rightChild;
    	    while (lookingAt->rightChild !=NULL)
    	    {
    	        lookingAt = lookingAt->rightChild;
    	        rHeight += 1;
    	    }
    	    //cout << "postDATA: " << this->data << endl;
    	    if (lHeight > rHeight)
    	    {
    	        return lHeight;
    	    }
    	    else
    	    {
    	        return rHeight;
    	    }
    	}