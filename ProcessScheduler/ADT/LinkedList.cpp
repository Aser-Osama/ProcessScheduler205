#include "LinkedList.h"
#include "../Process.h"

template<typename T>
void LinkedList<T>::PrintList()	const
{
	Node<T>* p = Head;

	while (p)
	{
		cout << p->getItem() << "\t";
		p = p->getNext();
	}
	cout << "\n";
}

template<>
 void LinkedList<Process*>::PrintList()	const
{
    Node<Process*>* p = Head;

    while (p)
    {
        cout << *(p->getItem()) << "\t";
        p = p->getNext();
    }
    cout << "\n";
}