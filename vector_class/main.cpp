#include "include/Vector.h"
#include <iostream>
#include <ostream>

int main() {
    vec3 v1(1,4,5), v2, v3;

    std::cout << "Enter second vector: " << '\n';
    std::cin >> v2;

    std::cout << "----------------------------------------------"<<'\n';
    std::cout << "v1: " << v1 << " v2: " << v2 << " v3: " << v3 << '\n';

    std::cout << "----------------------------------------------"<<'\n';
    std::cout << "module:  v1: " << ~v1 << ", v2: " << ~v2 << ", v3: " << ~v3 << '\n';

    std::cout << "----------------------------------------------"<<'\n';
    std::cout << "v1<v2: " <<  v1.operator<(v2) << "; v1>v2: " << v1.operator>(v2) << "; v1==v2: " << v1.operator==(v2) <<
        "; v1!=v2: " << v1.operator!=(v2) << "; v1>=v2: " << v1.operator>=(v2) << "; v1>=v2: " << v1.operator<=(v2) << '\n';

    std::cout << "----------------------------------------------"<<'\n';
    std::cout << "operator*: " << v1.operator*(5) << "; operator+: " << v1+v2 << "; operator-: " << v1-v2 <<
        "; operator+: " << +v1 << "; operator-: " << -v2 <<
        "; operator--: " << --v2 << ", " << v2 << "; " << v2-- << ", " << v2 <<
        "; operator++: " << ++v2 << ", " << v2 << "; " << v2++ << ", " << v2  << '\n';

    std::cout << "----------------------------------------------"<<'\n';
    std::cout << "operator[]: " << v2[1] << '\n';


    return 0;
}
