#pragma once
#include <iostream>
#include "../../Process.h"
using namespace std;
/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

				The Node: item of type T and a "next" pointer
					-------------
					| item| next | --->
					-------------
General Queue case:

				 frontPtr																backPtr
					\											   						/
					 \											  					   /
					------------- 	  ------------- 	  ------------- 	  -------------
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

				 frontptr	 backptr
						\	 /
						 \	/
					---- NULL ------


Single Node Case:
				 frontPtr	 backPtr
					\		/
					 \	   /
					-----------
					|item| next| -->NULL
					-----------

*/

#ifndef QUEUE_
#define QUEUE_

#include "QueueNode.h"
#include "QueueADT.h"
using namespace std;


template <typename T>
class Queue :public QueueADT<T>
{
private:
	int count = 0;
	queuenode<T>* backPtr;
	queuenode<T>* frontPtr;
public:
	Queue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	virtual void Print()  const;
	int getCount() const;
	~Queue();

	Queue(const Queue<T>& LQ);

	//copy constructor
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
Queue<T>::Queue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool Queue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool Queue<T>::enqueue(const T& newEntry)
{
	queuenode<T>* newqueuenodePtr = new queuenode<T>(newEntry);
	// Insert the new queuenode
	if (isEmpty())	//special case if this is the first queuenode to insert
		frontPtr = newqueuenodePtr; // The queue is empty
	else
		backPtr->setNext(newqueuenodePtr); // The queue was not empty

	backPtr = newqueuenodePtr;
	count++;
	// New queuenode is the last queuenode now
	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool Queue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	queuenode<T>* queuenodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (queuenodeToDeletePtr == backPtr)	 // Special case: last queuenode in the queue
		backPtr = nullptr;
	else
		delete queuenodeToDeletePtr;

	// Free memory reserved for the dequeued queuenode
	count--;
	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool Queue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all queuenodes from the queue by dequeuing them
*/
template <typename T>
Queue<T>::~Queue()
{
	//Note that the cout statements here is just for learning purpose
	//They should be normally removed from the destructor
	//cout << "\nStarting Queue destructor...";
	//cout << "\nFreeing all queuenodes in the queue...";

	//Free all queuenodes in the queue
	T temp;
	while (dequeue(temp));

	//cout << "\n Is Queue Empty now?? ==> " << boolalpha << isEmpty();
	//cout << "\nEnding Queue destructor..." << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: Queue<T>: The Queue to be copied
Output: none
*/

template <typename T>
Queue<T>::Queue(const Queue<T>& LQ)
{
	frontPtr = backPtr = nullptr;
	queuenode<T>* queuenodePtr = LQ.frontPtr;	//start at the front queuenode in LQ
	while (queuenodePtr)
	{
		enqueue(queuenodePtr->getItem());	//get data of each queuenode and enqueue it in this queue 
		queuenodePtr = queuenodePtr->getNext();
	}
}

template <typename T>
int Queue<T>::getCount() const
{
	return count;
}

template<>
inline void Queue<Process*>::Print() const
{
	if (isEmpty())
		return;


	queuenode<Process*>* tmpPtr = frontPtr;

	while (tmpPtr)
	{
		cout << *(tmpPtr->getItem()) << ", \t";
		tmpPtr = tmpPtr->getNext();
	}
}

template <typename T>
void Queue<T>::Print() const
{
	if (isEmpty())
		return;

	
	queuenode<T>* tmpPtr = frontPtr;

	while(tmpPtr)
	{
		cout << tmpPtr->getItem() << ",\t";
		tmpPtr = tmpPtr->getNext();
	}
}





#endif