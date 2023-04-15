#pragma once

#include "Pair.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

template<class T, class U>
class Map{
        LinkedList<Pair<T,U>> map;
        public:

        Map(){}
        Map<T,U>& operator = (const Map<T,U>  & rhs ){
            map.DeleteAll();
            Node<Pair<T,U>>* head=rhs.getHead();
            while(head){
                addPair(head->getItem().getKey(),head->getItem().getValue());
                head=head->getNext();
            }
            return *this;
        }

        Map(const Map<T,U> & rhs){
            map.DeleteAll();
            Node<Pair<T,U>>* head=rhs.getHead();
            while(head){
                addPair(head->getItem().getKey(),head->getItem().getValue());
                head=head->getNext();
            }
        }

        Node<Pair<T,U>>* getHead() const {
            return map.getHead();
        }
        
        void addPair(T k,U v){
            Pair<T,U> pair;
            pair.setPair(k,v);
            map.InsertEnd(pair);
        }

        bool getValue(T k,U& v){
            Node<Pair<T,U>>* head=map.getHead(); 
            while (head){
                if (head->getItem().getKey()==k){
                    v=head->getItem().getValue();
                    return true;
                }
                else{
                    return false;
                    }
                head=head->getNext();
                }
                return false;
        }

        bool updateValue(T k,U v){
            Node<Pair<T,U>>* head=map.getHead(); 
            while (head){
                        if (head->getItem().getKey()==k){
                                head->getItem().setValue(v);
                                return true;
                                }
                        else{
                                return false;
                                }
                head=head->getNext();
                }
                return false;
 
        }

        void displayMap(){
                Node<Pair<T,U>>* head=map.getHead(); 
                while (head){
                        cout<<"("<<head->getItem().getKey()<<","<<head->getItem().getValue()<<")"<<" ";
                        head=head->getNext();
                }
                cout<<endl;
        }

        bool deletePair(T k, U v){
            Pair<T,U> pair;
            pair.setPair(k,v);
            return map.DeleteNode(pair);
        }

};
