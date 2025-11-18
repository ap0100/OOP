#include <iostream>
using namespace std;


class Fraction{
    int numerator;
    int denumerator;

public:
    Fraction(const int numerator, const int denumerator=1){
        this->numerator=numerator;
        this->denumerator=denumerator;
        this->reduceFraction();
    }

    Fraction(const Fraction &original){
        this->numerator=original.numerator;
        this->denumerator=original.denumerator;
        this->reduceFraction();
    }

    Fraction() {
        this->numerator=0;
        this->denumerator=1;
    }

    Fraction& operator=(const Fraction& original){
        if(this!=&original){ //for no self-assignment
            this->numerator=original.numerator;
            this->denumerator=original.denumerator;
        }

        return *this;
    }

    int getN() const {return this->numerator;}
    int getD() const {return this->denumerator;}
    void setN(const int n) {this->numerator=n;}
    void setD(const int d) {this->denumerator=d;}

    void print() const {
        cout << this->numerator << "/" << this->denumerator <<'\n';
    }

    int GCD(int a, int b) const {
        if (b==0) return a;
        return GCD(b, a%b);
    }

    void reduceFraction() {
        int d=GCD(abs(this->numerator),abs(this->denumerator));
        if (d>1) {
            this->numerator/=d;
            this->denumerator/=d;
        }
    }

    Fraction operator*(const Fraction &b) const{
        Fraction c(*this);
        c.setN(this->numerator*b.getN());
        c.setD(this->denumerator*b.getD());
        c.reduceFraction();
        return c;
    }

    Fraction operator+(const Fraction &b) const {
        Fraction c(*this);
        if (this->denumerator==b.denumerator) {
            c.setN(this->numerator+b.numerator);
            return c;
        }
        c.setN(this->numerator*b.getD() + b.getN()*this->denumerator);
        c.setD(this->denumerator*b.getD());
        c.reduceFraction();
        return c;
    }

    Fraction operator-(const Fraction &b) const {
        Fraction c(*this);
        if (this->denumerator==b.denumerator) {
            c.setN(this->numerator-b.numerator);
            return c;
        }
        c.setN(this->numerator*b.getD() - b.getN()*this->denumerator);
        c.setD(this->denumerator*b.getD());
        c.reduceFraction();
        return c;
    }

    Fraction operator/(const Fraction &b) const {
        if (b.numerator==0) {
            cout << "invalid division";
            return {};
        }
        Fraction flippedB(b);
        flippedB.setN(b.denumerator);
        flippedB.setD(b.numerator);
        Fraction c = this->operator*(flippedB);
        c.reduceFraction();
        return c;
    }

    bool operator==(const Fraction &b) const {
        return this->numerator==b.numerator && this->denumerator==b.denumerator;
    }

    bool operator<(const Fraction &b) const {
        if (this->denumerator==b.denumerator) return this->numerator < b.numerator;
        return this->numerator*b.getD() < b.numerator*this->denumerator;
    }

    bool operator>(const Fraction &b) const {
        return !(*this<b) && !(*this==b);
    }

    ~Fraction(){}
};

ostream& operator<<(ostream& o, const Fraction &f){
    o << f.getN() << "/" << f.getD();
    return o;
}

int main()
{
    Fraction a(7,8), b(4,5);

    cout << "*: " << a*b << "\n/: " << a/b << "\n+: " << a+b << "\n-: " <<  a-b << "\n==: " << (a==b) << "\n<: " << (a<b) << "\n>: " << (a>b) << '\n';


    return 0;
}