#pragma once
#include"Node.h"
#include"ListInterface.h"
#include<exception>
template<class T>
class LinkedList:public ListInterface<T>
{
private:
	Node<T>*Head;
	int itemCount;
	Node<T>*getNodeat(int newposition);
public:
	LinkedList();
	LinkedList(const LinkedList<T>& LQ);//copyConstructor
	virtual bool isEmpty();
	virtual int getLength();
	virtual bool insert(int newposition,const T& newEntry);
	virtual bool remove(int newposition);
	virtual void clear();
	virtual T getEntry(int newposition);
	LinkedList<T>& operator=(LinkedList<T>& r);	//Assigment Operator
	~LinkedList();
};
template<class T>
LinkedList<T>::LinkedList()
{
	itemCount=0;
	Head=nullptr;
}
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& r)
{
	//LinkedList<T>*L=new LinkedList<T>;
	Node<T>*ptr=r.Head;
	itemCount=r.itemCount;
	if(ptr==nullptr)
	{
		Head=nullptr;
		return;
		/*return *L;*/
	}
	Node<T>*Headptr;
	Headptr=new Node<T>(ptr->getItem()); //ccopy th foirst node
	Head=Headptr;

	//copy ramining
	Node<T>*newptr=Headptr;
	ptr=ptr->getNext();
	while(ptr)
	{
		Node<T>*newnodeptr=new Node<T>(ptr->getItem());
		newptr->setNext(newnodeptr);

		ptr=ptr->getNext();
		newptr=newptr->getNext();
	}
}

template<class T>
LinkedList<T>& LinkedList<T>:: operator=(LinkedList<T>& r)
{
	Node<T>*ptr=r.Head;
	itemCount=r.itemCount;
	if(ptr==nullptr)
	{
		Head=nullptr;
		return *this;
	}
	Node<T>*Headptr;
	Headptr=new Node<T>(ptr->getItem()); //ccopy th foirst node
	Head=Headptr;

	//copy ramining
	Node<T>*newptr=Headptr;
	ptr=ptr->getNext();
	while(ptr)
	{
		Node<T>*newnodeptr=new Node<T>(ptr->getItem());
		newptr->setNext(newnodeptr);

		ptr=ptr->getNext();
		newptr=newptr->getNext();
	}
	return *this;
}

template<class T>
Node<T>*LinkedList<T>::getNodeat(int newposition)
{
	Node<T>*ptr=nullptr;
	if((newposition>=1)&&(newposition<=itemCount))
	{
		ptr=Head;
		for(int i=1;i<newposition;i++)
			ptr=ptr->getNext();
	}
	return ptr;
}
template<class T>
T LinkedList<T>::getEntry(int newposition)
{
	Node<T>*ptr;
	if((newposition>=1)&&(newposition<=itemCount))
		ptr=getNodeat(newposition);
	if(ptr)
		return ptr->getItem();
	else
	{
		exception e;
		throw (e);
	}

}
template<class T>
bool LinkedList<T>::insert(int newposition,const T& newEntry)
{
	if((newposition>=1)&&(newposition<=itemCount+1))
	{
		Node<T>*ptr=new Node<T>(newEntry);
		if(newposition==1)
		{
			ptr->setNext(Head);
			Head=ptr;
		}
		else
		{
			// Find node that will be before new node
			Node<T>* prevPtr = getNodeat(newposition - 1);
			// Insert new node after node to which prevPtr points
			ptr->setNext(prevPtr->getNext());
			prevPtr->setNext(ptr);
		} // end if
		itemCount++; // Increase count of entries
		return true;
	} // end if
	return false;
}
template < class T>
bool LinkedList<T>::remove( int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		Node<T>* curPtr = nullptr ;
		if (position == 1)
		{
			// Remove the first node in the chain
			curPtr = Head; // Save pointer to node
			Head = Head->getNext();
		}
		else
		{
			// Find node that is before the one to delete
			Node<T>* prevPtr = getNodeat(position - 1);
			// Point to node to delete
			curPtr = prevPtr->getNext();
			// Disconnect indicated node from chain by connecting the
			// prior node with the one after
			prevPtr->setNext(curPtr->getNext());
		} // end if
		// Return node to system
		curPtr->setNext( nullptr );
		//delete curPtr;
		curPtr = nullptr ;
		itemCount--; // Decrease count of entries
	} // end if
	return ableToRemove;
}
template <class T>
void LinkedList<T>::clear()
{
	while (!isEmpty())
		remove(1);
}
template <class T>
LinkedList<T>::~LinkedList()
{
	clear();
}
template <class T>
int LinkedList<T>::getLength()
{
	return itemCount;
}
template<class T>
bool LinkedList<T>::isEmpty()
{
	return (itemCount==0);
}