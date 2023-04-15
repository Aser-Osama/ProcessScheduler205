#pragma once

#include "Pair.h"
#include <iostream>

using namespace std;

template<class T, class U>
class Map{
        Pair<T,U> *map;
        int count=0;
        int size;
        public:
        Map(int s):size(s){
            map= new Pair<T,U>[size];
        }
        void addPair(T k,U v){
            if (count!=size){
                Pair<T,U> kv;
                kv.setPair(k,v);
                map[count]=kv;count++;
            }
        }

        bool getValue(T k,U& v){
                for (int i=0;i<count;i++){
                        if (map[i].getKey()==k){
                                v=map[i].getValue();
                                return true;
                        }
                        else{
                                return false;
                        }
                }
                return false;
        }

        int getcount(){return count;}

        bool updateValue(T k,U v){
                for (int i=0;i<count;i++){
                        if (map[i].getKey()==k){
                                map[i].setValue(v);
                                return true;
                                }
                        else{
                                return false;
                                }
                }
                return false;
 
        }

        void displayMap(){
                for (int i=0;i<count;i++){
                        cout<<"("<<map[i].getKey()<<","<<map[i].getValue()<<")"<<" ";
                }
                cout<<endl;
        }

        void deletePair(T k, U v){
                for (int i=0;i<count;i++){
                        if (map[i].getKey()==k && map[i].getValue()==v){
                                map[i]=Pair<T,U>();
                        }
                }
        }
};
