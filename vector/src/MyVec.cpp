#include "../include/MyVec.h"
#include <iostream>

MyVec::MyVec(int size, int value){
    int capacity=4;
    while(size>=capacity){
        capacity*=2;
    }

    this->size=size;
    this->capacity=capacity;

    this->elements=new int[capacity];
    for(int i=0; i<this->size; i++) elements[i]=value;

    std::cout<<"Constructing finished"<<'\n';
}

MyVec::~MyVec() {
    delete[] elements;
    std::cout<<"Destroying MyVec"<<'\n';
}

void MyVec::_copy(const MyVec& orig) {
    this->size=orig.size;
    this->capacity=orig.capacity;
    this->elements=new int[this->capacity];
    for (int i=0; i<this->size; i++) elements[i]=orig.elements[i];
}

MyVec::MyVec(const MyVec& orig) {
    _copy(orig);
}

MyVec& MyVec::operator=(const MyVec& orig) {
    if (this!=&orig) {
        delete [] elements;
        _copy(orig);
    }
    return *this;
}

void MyVec::print() {
    std::cout<<"capacity: " << this->capacity << ", size: " << this->size << ", elements: ";
    for (int i=0; i<this->size; i++) std::cout<<this->elements[i]<<' ';
    std::cout<<'\n';
}

void MyVec::push(int val) {
    if (this->size==this->capacity) {
        this->capacity*=2;
        int *tmp=new int[this->capacity];
        for (int i=0; i<this->size; i++) tmp[i]=this->elements[i];
        delete [] this->elements;
        this->elements=tmp;
    }

    this->elements[this->size]=val;
    this->size++;
}

void MyVec::reduce_capacity() {
    if (this->size<this->capacity/2) {
        int new_capacity=0;
        this->capacity/2 > 4 ? new_capacity=this->capacity/4 : new_capacity=this->capacity;
        int *newElements=new int[new_capacity];
        for (int i=0; i<this->size; i++) newElements[i]=this->at(i);
        delete [] this->elements;
        this->elements=newElements;
        this->capacity=new_capacity;
    }
}

void MyVec::pop() {
    if (empty()) {
        std::cout<<"Popping from empty vector"<<'\n';
        return;
    }

    this->size--;
    reduce_capacity();
}

int MyVec::operator[](int index){
    if (index<0 || index>this->size-1) return -1;
    return this->elements[index];
}

int MyVec::get_size() {
    return this->size;
}

bool MyVec::empty() {
    return this->size==0;
}

int& MyVec::at(const int pos) {
    if (pos<0 || pos>this->size) {
        std::cout<<"Trying to access an invalid position"<<"; ";
        return this->front();
    }
    return this->elements[pos];
}

int& MyVec::front() {
    if (empty()) throw std::out_of_range("MyVec is empty");
    return this->elements[0];
}

int& MyVec::back() {
    if (empty()) throw std::out_of_range("MyVec is empty");
    return this->elements[this->size-1];
}

int& MyVec::data() {
    return this->elements[0];
}

void MyVec::sort() {
    for (int i=0; i<this->size-1; i++) {
        for (int j=i+1; j<this->size; j++) {
            if (this->elements[i]>this->elements[j]) {
                int tmp=this->elements[i];
                this->elements[i]=this->elements[j];
                this->elements[j]=tmp;
            }
        }
    }
}

MyVec MyVec::operator+(const MyVec& other) {
    MyVec newVec(this->size+other.size, 0);
    int i;
    for (i=0; i<this->size; i++) newVec.elements[i]=this->elements[i];
    for (i=0; i<other.size; i++) newVec.elements[i+this->size]=other.elements[i];
    return newVec;
}
