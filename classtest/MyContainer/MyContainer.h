#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include <iostream>

class MyContainer {
public:
    MyContainer(int size);
    ~MyContainer();
    MyContainer(const MyContainer &Other);
    MyContainer &operator=(const MyContainer &Other);

    int size() const;
    int* data() const;
    static int count();

private:
    int *_data{nullptr};
    int _size{0};
    static int _count;
};

#endif // MYCONTAINER_H