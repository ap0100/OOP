#include "include/MyVec.h"
#include <iostream>
#include <ostream>


int main() {
    MyVec v(3, 123), v1(1, 0);

    std::cout << "----------------------------------------------"<<'\n';
    v.print();
    v1.print();
    std::cout << "----------------------------------------------"<<'\n';
    std::cout << "push: " << '\n';
    for (int i=4; i<50; i*=2) v.push(i);
    v.print();

    std::cout << "----------------------------------------------"<<'\n';
    std::cout<< "at: " << v.at(8) << ", back: " << v.back() << ", front: " << v.front() << ", data: " << v.data() << '\n';

    v.at(1)=3;
    std::cout<< "at: " << v.at(1) << '\n';

    v.print();

    std::cout << "----------------------------------------------"<<'\n';
    std::cout<< "operator[]: " << v[45]<<", "<<v[2]<<", "<<v[v.get_size()-1]<<", "<<v[v.get_size()]<<'\n';

    std::cout << "----------------------------------------------"<<'\n';
    std::cout << "operator+: " << '\n';
    MyVec v2 = v+v1;
    v2.print();

    std::cout << "----------------------------------------------"<<'\n';
    std::cout << "sorting: " << '\n';
    v2.sort();
    v2.print();

    std::cout << "----------------------------------------------"<<'\n';
    std::cout << "testing capacity reduction and pop: " << '\n';
    for (int i=0; i<4; i++) v.pop();
    v.print();
    v1.pop();
    v1.print();

    std::cout << "----------------------------------------------"<<'\n';

    return 0;
}
