#pragma once


template<class T, class U>
class Pair{
        T key; U value;
        public:
        void setPair(T k, U v){
                key=k;value=v;
        }

        T getKey() const{
                return key;
        }

        U getValue ()const{
                return value;
        }

        void setValue (U v){
                value=v;
        }
        
        bool operator==(Pair<T,U> pair){
                if(pair.getKey()==this->key&&pair.getValue()==this->value)
                        return true;
                else
                        return false;
        }
};

