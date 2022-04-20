#pragma once

template<class T>
class PriortiyQueueADT
{
public:

   virtual bool isEmpty() const = 0;

   virtual bool enqueue(const T& newEntry,const int& p) = 0;
 
   virtual bool dequeue(T& FrontEntry) = 0;

   virtual bool peek(T& FrontEntry) const = 0;

   virtual ~PriortiyQueueADT() {}
};

