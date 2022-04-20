#pragma once
template < typename T>
class PriorityNode
{
private :
	int priority;
	T item; // A data item
	PriorityNode<T>* next; // Pointer to next node
public :
	PriorityNode();
	PriorityNode( const T & r_Item,int P);	
	PriorityNode( const T & r_Item, PriorityNode<T>* nextNodePtr);
	PriorityNode( const T & r_Item, int P,PriorityNode<T>* nextNodePtr);
	void setItem( const T & r_Item);
	void setNext( PriorityNode<T>* nextNodePtr);
	void setPriority(const int& P);
	T getItem() const ;
	PriorityNode<T>* getNext() const ;
	int getPriority() const;
};
template < typename T>
PriorityNode<T>::PriorityNode() 
{
	next = nullptr;
} 

template < typename T>
PriorityNode<T>::PriorityNode( const T & r_Item,int p)
{
	priority=p;
	item = r_Item;
	next = nullptr;
} 

template < typename T>
PriorityNode<T>::PriorityNode( const T& r_Item,PriorityNode<T>* nextNodePtr)
{
	priority=-1;
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
PriorityNode<T>::PriorityNode( const T & r_Item, int P,PriorityNode<T>* nextNodePtr)
{
	priority=p;
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void PriorityNode<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void  PriorityNode<T>::setNext( PriorityNode<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T PriorityNode<T>::getItem() const
{
	return item;
} 

template < typename T>
PriorityNode<T>* PriorityNode<T>::getNext() const 
{
	return next;
} 
template < typename T>
int PriorityNode<T>::getPriority() const
{
	return priority;
}
template < typename T>
void PriorityNode<T>::setPriority(const int& P)
{
	priority=p;
} 