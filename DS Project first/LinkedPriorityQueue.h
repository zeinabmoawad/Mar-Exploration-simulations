#pragma once
#include "PriorityNode.h"
#include "PriortiyQueueADT.h"
#include <vector>
using namespace std;
template <typename T>
class LinkedPriorityQueue:public PriortiyQueueADT<T>
{

	PriorityNode<T>* backPtr;
	PriorityNode<T>* frontPtr;
public:
	LinkedPriorityQueue<T>& operator=(LinkedPriorityQueue<T>& r);
	LinkedPriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry,const int& p);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~LinkedPriorityQueue();

	//copy constructor
	LinkedPriorityQueue(const LinkedPriorityQueue<T> & LQ);
};
template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}
template <typename T>
bool LinkedPriorityQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}
template <typename T>
bool LinkedPriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	PriorityNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;

}
template <typename T>
bool LinkedPriorityQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template <typename T>
LinkedPriorityQueue<T>::~LinkedPriorityQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}
template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue(const LinkedPriorityQueue<T> & LQ)
{
	PriorityNode<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	PriorityNode<T>* ptr = new PriorityNode<T>(NodePtr->getItem(),NodePtr->getPriority());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		PriorityNode<T>* ptr = new PriorityNode<T>(NodePtr->getItem(),NodePtr->getPriority());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}
template <typename T>
bool LinkedPriorityQueue<T>::enqueue(const T& newEntry,const int& p)
{
	PriorityNode<T>* newNodePtr = new PriorityNode<T>(newEntry,p);
	if (isEmpty())	//special case if this is the first node to insert
	{
		frontPtr = newNodePtr; 
		backPtr=newNodePtr;
		return true;
	}
	if(frontPtr->getPriority()<p)
	{
		newNodePtr->setNext(frontPtr);
		frontPtr=newNodePtr;
		return true;
	}
	PriorityNode<T>* ptr=frontPtr;
	while(ptr->getNext())
	{
		if(ptr->getNext()->getPriority()<p)
		{
			newNodePtr->setNext(ptr->getNext());
			ptr->setNext(newNodePtr);
			return true;
		}
		ptr=ptr->getNext();
	}
	ptr->setNext(newNodePtr);
	backPtr=newNodePtr;
	return true;
} // end enqueue
template <typename T>
LinkedPriorityQueue<T>& LinkedPriorityQueue<T>::operator=(LinkedPriorityQueue<T>& r)
{

	PriorityNode<T>* NodePtr = r.frontPtr;
	if (!NodePtr) //r is empty
	{
		frontPtr = backPtr = nullptr;
		return *this;
	}

	//insert the first node
	PriorityNode<T>* ptr = new PriorityNode<T>(NodePtr->getItem(), NodePtr->getPriority());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		PriorityNode<T>* ptr = new PriorityNode<T>(NodePtr->getItem(), NodePtr->getPriority());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
	return *this;
}