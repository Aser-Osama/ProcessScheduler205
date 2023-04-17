#pragma once
#pragma once
#include "MinHeap.h"

template<typename T>
class PriorityQueue
{
public:
	PriorityQueue()
	{}
	void Enqueue(T newElement)
	{
		Heap.insertKey(newElement);
	}
	bool Dequeue(T& removedElement)
	{
		return Heap.extractMin(removedElement);
	}
	bool peek(T& frontElement) const
	{
		return Heap.peek(frontElement);
	}
	bool isEmpty() const
	{
		return Heap.isEmpty();
	}

private:
	MinHeap<T> Heap;
};

