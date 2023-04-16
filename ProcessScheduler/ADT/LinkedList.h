#pragma once
#ifndef _LINKEDLIST
#define _LINKEDLIST
#include "node.h"
#include <iostream>
using namespace std;


template <typename T>
class LinkedList
{
private:
        int count=0;
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:
        
        Node<T>* getHead() const{
                return Head;
        }

	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
    int getCount()const{
        return count;
    }
    LinkedList(const LinkedList& RHS)
    {
        count=RHS.getCount();
        Head = nullptr;
        Node<T>* tmpptr = RHS.Head;
        while (tmpptr)
        {
            this->InsertEnd(tmpptr->getItem());
            tmpptr = tmpptr->getNext();
        }
    }


	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
    void PrintList() const;
	
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
                count++;
	}
	
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
                count=0;
	}

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
        //
        //
        void InsertEnd(const T & data){
                Node<T> *P=Head;
                Node<T>* NewItem =new Node<T>(data);

                if(Head){
                        while (P->getNext()){
                                P=P->getNext();
                        }
                        P->setNext(NewItem);
                }
                else{
                        this->InsertBeg(data);
                }
                count++;
        }

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
        //
        bool Find(const T & data){

                Node<T> *P=Head;

                while (P->getNext()){
                        P=P->getNext();
                        if (P->getItem()==data){
                                return true;
                        }
                }
                return false;
        }

//
//	//[3]CountOccurance
//	//returns how many times a certain value appeared in the list
        int CountOccurance(const T & data){
                
                if (Head->getNext()){
                        Node<T> *P=Head;
                        int Occurance=0;
                        while (P->getNext()){
                                P=P->getNext();
                                if (P->getItem()==data){
                                        Occurance++;
                                }
                        }
                        return Occurance;
                        
                }
                return 0;
        }

//
//
//        
	//[4] DeleteFirst
	//Deletes the first node in the list

        void DeleteFirst(){
                
                if (Head){
                        Node<T>* P=Head;
                        Head=Head->getNext();
                        delete P;
                        
                }
                count--;
        }

//
//	//[6] DeleteNode
//
//	//deletes the first node with the given value (if found) and returns true
//	//if not found, returns false
//	//Note: List is not sorted
//
        bool DeleteNode(const T & data){
                Node<T> *P=Head;
                Node<T> *N=Head->getNext();
                
                if (Head){
                        if (P->getItem()==data){
                                DeleteFirst();
                                return true;
                        }
        
                        while (N->getNext()){
                                P=P->getNext();
                                N=N->getNext();
        
                                if (N->getItem()==data){
                                        P->setNext(N->getNext());
                                        delete N;
                                        return true;
                                }
        
                        }
                        
                }
                count--;
                return false;
        }

//
//
//	//[7] DeleteNodes
//	//deletes ALL node with the given value (if found) and returns true
//	//if not found, returns false
//	//Note: List is not sorted
        bool DeleteNodes(const T & data){
                Node<T> *P=Head;
                Node<T> *N=Head->getNext();
                bool condition=false;
                if (Head->getNext()){
                        if (P->getItem()==data){
                                P=P->getNext();
                                N=N->getNext();
                                DeleteFirst();
                                condition=true;
                                count--;
                        }
        
                        while (N->getNext()){
                                P=P->getNext();
                                N=N->getNext();
        
                                if (N->getItem()==data){
                                        P->setNext(N->getNext());
                                        delete N;
                                        N=P->getNext();
                                        condition=true;
                                        count--;
                                }
        
                        }
                        
                }
                return condition;
        }

//
//
//
//
//	//[8]Merge
//	//Merges the current list to another list L by making the last Node in the current list 
//	//point to the first Node in list L
//        //
        void Merge(LinkedList<T>* List){
                Node<T> * P=Head; 
                if(!Head && !(List->getHead())){
                        while (P->getNext()!=NULL){
                                P=P->getNext();
                        }
                        P->setNext(List->getHead());
                        count+=List->getCount();
                        
                        }
        }
//	//[9] Reverse
//	//Reverses the linked list (without allocating any new Nodes)
//        //
//        //
        void Reverse(){
                cout<<"im in here";
                if (Head){
                
                cout<<"im in main!";
                Node<T> *i=Head;
                Node<T> *p=Head->getNext();
                Node<T> *o=NULL;
                
                i->setNext(NULL);
                while(p){
                        o=p->getNext();
                        p->setNext(i);
                        i=p;p=o;
                        }
                Head=i;cout<<"i did this";
                }
                
        }

};




#endif

