#include "Node.h"
#include <iostream>
using namespace std;

        Node::Node()
        {
            data = -314159;
            leftChild = NULL;
            rightChild = NULL;
        }
        Node::Node(int data) 
        {
            //cout << "new node created with data = " << data << " and no children" << endl;
            this->data = data;
            leftChild = NULL;
            rightChild = NULL;
        }
        Node::Node(int data, Node * leftChild, Node * rightChild) 
        {
            this->data = data;
            this->rightChild = rightChild;
            this->leftChild = leftChild;
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
    	    int lHeight = 0;
    	    Node * lookingAt = this;
    	    while (lookingAt->leftChild !=NULL)
    	    {
    	        lookingAt = lookingAt->leftChild;
    	        lHeight += 1;
    	    }
    	    
    	    int rHeight = 0;
    	    lookingAt = this;
    	    while (lookingAt->rightChild !=NULL)
    	    {
    	        lookingAt = lookingAt->rightChild;
    	        rHeight += 1;
    	    }
    	    if (lHeight > rHeight)
    	    {
    	        return lHeight;
    	    }
    	    else
    	    {
    	        return rHeight;
    	    }
    	}