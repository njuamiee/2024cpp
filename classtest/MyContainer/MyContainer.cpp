#include "MyContainer.h"

int MyContainer::_count = 0;

MyContainer::MyContainer(int size) : _size(size) {
    _data = new int[_size];
    _count++;
}

MyContainer::~MyContainer() {
    delete[] _data;
    _count--;
}

MyContainer::MyContainer(const MyContainer &Other) : _size(Other._size) {
    _data = new int[_size];
    _count++;
    for(int i = 0; i < _size; i++){
        _data[i] = Other._data[i];
    }
}

MyContainer& MyContainer::operator=(const MyContainer &Other) {
    if(this == &Other){
        return *this;
    }
    delete[] _data;
    _size = Other._size;
    _data = new int[_size];
    for(int i = 0; i < _size; i++){
        _data[i] = Other._data[i];
    }
    return *this;
}

int MyContainer::size() const {
    return _size;
}

int* MyContainer::data() const {
    return _data;
}

int MyContainer::count() {
    return _count;
}