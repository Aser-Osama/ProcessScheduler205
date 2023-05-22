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
        cout << *(p->getItem()) << ", \t";
        p = p->getNext();
    }
}

 template<typename T>
 bool LinkedList<T>::Find(const T& data) {

     Node<T>* P = Head;

     while (P->getNext()) {
         P = P->getNext();
         if (P->getItem() == data) {
             return true;
         }
     }
     return false;
 }

 template<>
 bool LinkedList<Process*>::Find(Process* const &data) {

     if (!Head) { return false; }
     if (Head->getItem() == data) return true;

     Node<Process*>* P = Head;
     while (P->getNext()) {
         if (*(P->getItem()) == *(data)) {
             return true;
         }
         P = P->getNext();
     }
     return false;
 }