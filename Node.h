#pragma once

#include "NodeInterface.h"
#include <iostream>
using namespace std;

class Node :
    public NodeInterface
{
    public :
        Node();
        Node(int data);
        Node(int data, Node * p);
    	~Node();
    	int getData() const;
    	Node * getLeftChild() const;
    	Node * getRightChild() const;
    	bool setData(int data);
    	bool setLeftChild(Node * newLeftChild);
    	bool setRightChild(Node * newRightChild);
    	int getHeight();
    	int getLeftHeight();
    	int getRightHeight();
    private :
        int data;
        Node * rightChild;
        Node * leftChild;
        Node * parent;
        friend class AVL;
};