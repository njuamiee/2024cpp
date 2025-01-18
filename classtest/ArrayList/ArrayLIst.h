#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <optional>
#include <cstring>
#include <iostream>
using namespace std;
// TODO: 在这里编写你的ArrayList类
template <typename T>
class ArrayList {
    private:
    T* elements;
    int count;
    int maxCapacity;
    
    void increaseCapacity(int newCapacity){
        T* newElements = new T[newCapacity];
        for(int i = 0; i < count; i++){
            newElements[i] = elements[i];
        }
        elements = newElements;
        maxCapacity = newCapacity;
    }
    public:
    ArrayList() : count(0), maxCapacity(10) {
        elements = new T[maxCapacity];
    }
    
    int getSize(){
        return count;
    }
    
    int getCapacity(){
        return maxCapacity;
    }
    
    void add(const T& n){
        if(count == maxCapacity){
            increaseCapacity(maxCapacity + maxCapacity / 2);
        }
        elements[count] = n;
        count++;
    }
       
    void remove(const T& n){
        int sign = 0;
        for(int i = 0; i < count; i++){
            if(sign){
                elements[i - 1] = elements[i];
            }else if(n == elements[i] && !sign){
                sign = 1;
            }
        }
        if(sign){
            count--;
            elements[count] = T{};
        }
    }
    
    optional<T> get(int index) const{
        if(index < 0 || index >= count){
            return nullopt;
        }
        return elements[index];
    }
};
#endif // ARRAYLIST_H