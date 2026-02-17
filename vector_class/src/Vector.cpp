#include "../include/Vector.h"

#include <cmath>

vec3::vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void vec3::copy(const vec3& original) {
    this->x = original.x;
    this->y = original.y;
    this->z = original.z;
}

vec3::vec3(const vec3 &original) {
   copy(original);
}

vec3& vec3::operator=(const vec3& original) {
    if (this != &original) this->copy(original);
    return *this;
}

vec3::~vec3() {}

float vec3::operator~() const {
    return sqrtf(x * x + y * y + z * z);
}

vec3 vec3::operator+() const {
    //return *this;
    return vec3(1, 1, 1);
}

vec3 vec3::operator-() const {
    return vec3(-x, -y, -z);
}

bool vec3::operator==(const vec3& other) const {
    return this->x==other.x && this->y==other.y && this->z==other.z;
}

bool vec3::operator!=(const vec3& other) const {
    return !(*this == other);
}

bool vec3::operator<(const vec3& other) const {
    if (this->x<other.x) return true;
    if (this->x>other.x) return false;
    if (this->y<other.y) return true;
    if (this->y>other.y) return false;
    return this->z<other.z;
}

bool vec3::operator>(const vec3& other) const {
    return !(*this<other);
}

bool vec3::operator<=(const vec3& other) const {
    return *this<other || *this==other;
}

bool vec3::operator>=(const vec3& other) const {
    return !(*this<=other);
}

float vec3::operator[](const int index) const {
    switch (index) {
        case 0: return this->x;
        case 1: return this->y;
        case 2: return this->z;
        default: return -1;
    }
}

vec3 vec3::operator*(float number) const {
    return vec3(this->x*number, this->y*number, this->z*number);
}

vec3 vec3::operator+(const vec3 &other) const {
    return vec3(this->x+other.x, this->y+other.y, this->z+other.z);
}

vec3 vec3::operator-(const vec3& other) const {
    return vec3(this->x-other.x, this->y-other.y, this->z-other.z);
}

vec3& vec3::operator++() {
    //post-increment
    this->x+=1;
    this->y+=1;
    this->z+=1;
    return *this;
}

vec3& vec3::operator--() {
    //post-decerement
    this->x-=1;
    this->y-=1;
    this->z-=1;
    return *this;
}

vec3 vec3::operator++(int) {
    vec3 t(*this);
    this->x+=1;
    this->y+=1;
    this->z+=1;
    return t;
}

vec3 vec3::operator--(int) {
    vec3 t(*this);
    this->x-=1;
    this->y-=1;
    this->z-=1;
    return t;
}

ostream& operator<<(ostream& o, const vec3& v) {
    o << "(" << v.x << "," << v.y << "," << v.z << ")";
    return o;
}

istream& operator>>(istream& o, vec3& v) {
    o >> v.x >> v.y >> v.z;
    return o;
}