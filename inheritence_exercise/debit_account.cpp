#include <iostream>
#include <cstring>
using namespace std;

class DebitAccount {
    char name[100];
    long acc_number;
    double balance;

    public:
        DebitAccount(const char *name, const long acc_number=0, const double balance=0.0) {
            strncpy(this->name, name, 99);
            this->name[99]='\0';
            this->acc_number=acc_number;
            this->balance=balance;
        };

        double get_balance() const { return this->balance; }

        void show_info() const {
            cout << "Name: " << this->name << "\nAccount Number: " << this->acc_number << "\nBalance: " << this->balance << '\n';
        }

        void deposit(const double amount) {
            if (amount>=0) balance+=amount;
            else cout << "you can't deposit negative amount!" << '\n';
        }

         void withdraw(const double amount) {
             if (amount<0) cout << "you can't withdraw negative amount!" << '\n';
             if (amount>this->balance) cout << "you can't withdraw more money than you have in your account!" << '\n';
             else balance-=amount;
        }

        ~DebitAccount() {};
};

class CreditAccount : public DebitAccount {
    double limit;
    double interest;
    double minus;

    public:
    CreditAccount(const char *name="----", const long number=0,
            const double balance=0, const double limit=1000,
            const double interest=0.05, const double minus=0): DebitAccount(name, number, balance) {
        this->limit = limit;
        this->interest = interest;
        this->minus = minus;
    }

    void show_info() const {
        DebitAccount::show_info();
        cout << "Limit: " << this->limit << "\nInterest: " << this->interest << "\nMinus: " << this->minus << '\n';
    }

    void withdraw(const double amount) {
        double balance=get_balance();

        if (amount<0) cout << "you can't withdraw negative amount!" << '\n';
        if (amount>balance) cout << "you can't withdraw more money than you have in your account!" << '\n';
        else if (amount<=balance) DebitAccount::withdraw(amount);
        else if (amount<=(balance+this->limit-this->minus)) {
            double advance=amount-balance;
            this->minus+=advance*(1.0+this->interest);
            deposit(advance);
            DebitAccount::withdraw(amount);
        }
    }

    ~CreditAccount() {};
};

int main() {
    DebitAccount d("Pero Perovski", 6, 100000);
    CreditAccount ca("Mitko Mitkovski", 10, 5000, 1000);
    d.show_info();
    d.deposit(50000);
    d.withdraw(600000);
    d.show_info();
    ca.show_info();
    ca.deposit(500);
    ca.show_info();
    ca.withdraw(6200);
    ca.show_info();

    return 0;
}