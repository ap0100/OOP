#ifndef VECTOR_CLASS_VECTOR_H
#define VECTOR_CLASS_VECTOR_H

#endif //VECTOR_CLASS_VECTOR_H

#include <iostream>
using namespace std;

class vec3 {
    //koordinaten pochetok se zema so koordinati (0,0,0)
    float x,y,z;

    void copy(const vec3& original);

    public:
        vec3(float x=1, float y=1, float z=1); //default unit vector
        vec3& operator=(const vec3& original);
        vec3(const vec3 &other);

        float operator~() const;
        vec3 operator+(const vec3& other) const;
        vec3 operator+() const;
        vec3 operator-() const;
        vec3 operator-(const vec3& other) const;
        vec3 operator*(float number) const; //scalar multiplication - broj*vektor
        bool operator<(const vec3& other) const;
        bool operator>(const vec3& other) const;
        bool operator==(const vec3& other) const;
        bool operator<=(const vec3& other) const;
        bool operator>=(const vec3& other) const;
        bool operator!=(const vec3& other) const;
        vec3& operator++();
        vec3 operator++(int);
        vec3& operator--();
        vec3 operator--(int);
        float operator[](int index) const;


        friend ostream& operator<<(ostream& o, const vec3& v);
        friend istream& operator>>(istream& o, vec3& v);

        ~vec3();
};