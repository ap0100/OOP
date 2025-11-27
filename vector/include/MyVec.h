#ifndef UNTITLED_MYVEC_H
#define UNTITLED_MYVEC_H

class MyVec {
    int size;
    int capacity;
    int *elements;

    void _copy(const MyVec& orig);

    void reduce_capacity();

    public:
        MyVec(int size=0, int value=0);
        ~MyVec();
        MyVec(const MyVec& orig);
        MyVec& operator=(const MyVec& orig);
        int get_size();
        void print();
        void push(int val);
        void pop();
        int operator[](int index);

        int& at(int pos);
        int& front();
        int& back();
        bool empty();
        int& data();
        void sort();
        MyVec operator+(const MyVec& other);
};

#endif //UNTITLED_MYVEC_H