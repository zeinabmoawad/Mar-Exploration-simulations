#ifndef LIST_INTERFACE
#define LIST_INTERFACE
template<class T>
class ListInterface
{
public:
	virtual bool isEmpty()=0;
	virtual int getLength()=0;
	virtual bool insert(int newposition,const T& newEntry)=0;
	virtual bool remove(int newposition)=0;
	virtual void clear()=0;
	virtual T getEntry(int newposition)=0;
	virtual ~ListInterface(){}
};
#endif