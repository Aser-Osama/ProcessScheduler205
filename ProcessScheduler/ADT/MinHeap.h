#pragma once
#include "Process.h"
using namespace std;

template<typename T>
class MinHeap {
private:
	T* Array;    // pointer to the array of elements in the heap

	int capacity;  // maximum possible size on min heap

	int heap_size; // current number of elements in min heap
public:
	MinHeap()
	{
		heap_size = 0;
		capacity = 30;
		Array = new T[capacity];
	}
	~MinHeap()
	{
		delete[] Array;
	}

	int height()
	{
		return ceil(log2(heap_size + 1)) - 1;

	}

	int parent(int index)
	{
		return (index - 1) / 2;
	}

	int left(int index)
	{
		return (2 * index + 1);
	}

	int right(int index)
	{
		return (2 * index + 2);
	}

	void insertKey(const T& key)
	{
		// reallocates a new array to insert more keys

		if (heap_size == capacity)
			resizeArray(Array, heap_size, capacity);

		// inserts the new key at the end

		heap_size++;
		int index = heap_size - 1;
		Array[index] = key;

		// ensures that a min heap property is not violated.
		// every parent of a subtree is smaller than all of its descendants 

		while (index != 0 && Array[parent(index)] > Array[index])
		{
			T temp = Array[parent(index)];
			Array[parent(index)] = Array[index];
			Array[index] = temp;
			index = parent(index); // updating the parent
		}
		
	}

	bool extractMin(T& root)
	{
		if (heap_size == 0)
			return false;
		else if (heap_size == 1)
		{
			heap_size--;
			root = Array[0];
			return true;
		}
		root = Array[0];
		Array[0] = Array[heap_size - 1];
		heap_size--;
		MinHeapify(0);
		return true;
	}

	// a function to reconstruct the heap 
	void MinHeapify(int i)
	{
		int left_element = left(i);
		int right_element = right(i);
		int smallest = i;
		if (left_element < heap_size && Array[left_element] < Array[i])
		{
			smallest = left_element;
		}
		if (right_element < heap_size && Array[right_element] < Array[smallest])
		{
			smallest = right_element;
		}
		if (smallest != i)
		{
			// swapping to ensure that the parent is always less than its children

			T temp = Array[i];
			Array[i] = Array[smallest];
			Array[smallest] = temp;
			MinHeapify(smallest); // reconstructing the heap recursively
		}
	}

	bool isEmpty() const
	{
		return heap_size == 0;
	}

	bool peek(T& frontElement) const
	{
		if (isEmpty())
			return false;
		frontElement = Array[0];
		return true;
	}
	void resizeArray(T*& arr, int& size, int& capacity) {
		capacity += 20;
		T* temp = new T[capacity];
		for (int i = 0; i < size; i++) {
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}

};





template<>
class MinHeap<Process*> {
private:
	Process** Array;    // pointer to the array of elements in the heap

	int capacity;  // maximum possible size on min heap

	int heap_size; // current number of elements in min heap
public:
	MinHeap()
	{
		heap_size = 0;
		capacity = 30; // intially, it has 30 elements  
		Array = new Process * [capacity];
	}
	~MinHeap()
	{
		for (int i = 0; i < heap_size; i++) {
			delete[] Array[i]; // free memory for each pointer
		}
		delete[] Array;
	}

	int parent(int index)
	{
		return (index - 1) / 2;
	}

	int left(int index)
	{
		return (2 * index + 1);
	}

	int right(int index)
	{
		return (2 * index + 2);
	}

	bool insertKey(Process*& key)
	{
		if (heap_size == capacity)
			return false;

		// inserts the new key at the end
		heap_size++;
		int index = heap_size - 1;
		Array[index] = key;

		// ensures that a min heap property is not violated.
		// every parent of a subtree is smaller than all of its descendants 

		while (index != 0 && Array[parent(index)] > Array[index])
		{
			Process* temp = Array[parent(index)];
			Array[parent(index)] = Array[index];
			Array[index] = temp;
			index = parent(index); // updating the parent
		}
		return true;
	}

	bool extractMin(Process*& root)
	{
		if (heap_size == 0)
			return false;
		else if (heap_size == 1)
		{
			heap_size--;
			root = Array[0];
			return true;
		}
		root = Array[0];
		Array[0] = Array[heap_size - 1];
		heap_size--;
		MinHeapify(0);
		return true;
	}

	// a function to reconstruct the heap 
	void MinHeapify(int i)
	{
		int left_element = left(i);
		int right_element = right(i);
		int smallest = i;
		if (left_element < heap_size && Array[left_element] < Array[i])
		{
			smallest = left_element;
		}
		if (right_element < heap_size && Array[right_element] < Array[smallest])
		{
			smallest = right_element;
		}
		if (smallest != i)
		{
			// swapping to ensure that the parent is always less than its children

			Process* temp = Array[i];
			Array[i] = Array[smallest];
			Array[smallest] = temp;
			MinHeapify(smallest); // reconstructing the heap recursively
		}
	}
};