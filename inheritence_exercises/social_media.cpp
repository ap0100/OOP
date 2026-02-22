#include <iostream>
#include <cstring>
using namespace std;

class User {
    char *username;
    char *company;
    int position;

    void copy(const User &u) {
        this->username=new char[strlen(u.username)+1];
        strcpy(this->username,u.username);
        this->company=new char[strlen(u.company)+1];
        strcpy(this->company,u.company);
        this->position=u.position;
    }

    public:
        User(const char *username="", const char *company="", const int position=0) {
            this->username=new char[strlen(username)+1];
            strcpy(this->username,username);
            this->company=new char[strlen(company)+1];
            strcpy(this->company,company);
            this->position=position;
        }

        User(const User &u) {
            copy(u);
        }

        User &operator=(const User &u) {
            if (this!=&u) {
                delete [] this->username;
                delete [] this->company;
                copy(u);
            }
            return *this;
        }

        char *getUsername() const {return this->username;};
        char *getCompany() const {return this->company;};
        int getPosition() const {return this->position;};

        void setUsername(const char *username) {
            delete [] this->username;
            this->username=new char[strlen(username)+1];
            strcpy(this->username,username);
        }

        void setCompany(const char *company) {
            delete [] this->company;
            this->company=new char[strlen(company)+1];
            strcpy(this->company,company);
        }

        void setPosition(const int position) {
            this->position=position;
        }

        friend ostream &operator<<(ostream &os, const User &u);
        friend istream &operator>>(istream &is, User &u);

        bool operator==(const User &u) const {
            return strcmp(this->username,u.username)==0;
        }

        ~User() {
            delete [] this->username;
            delete [] this->company;
        }
};

ostream &operator<<(ostream &os, const User &u) {
    os << "Username: " << u.username << "\nCompany: " << u.company << ", Position: " << u.position << '\n';
    return os;
}

istream &operator>>(istream &is, User &u) {
    char username[1000], company[1000];
    int position;
    is >> username >> company >> position;

    u.setUsername(username);
    u.setCompany(company);
    u.setPosition(position);

    return is;
}

class Group {
    protected:
        User *participants;
   	    int numOfParticipants;
   	    string groupName;

        void copy(const Group &g){
	         this->numOfParticipants=g.numOfParticipants;
	         this->groupName=g.groupName;
             this->participants=new User[this->numOfParticipants];
             for(int i=0; i<this->numOfParticipants; i++) this->participants[i]=g.participants[i];
	    }

    public:
         Group(const char *groupName) : groupName(groupName), numOfParticipants(0), participants(new User[0])  {}

         Group(const Group &g) { copy(g); }

         Group &operator=(const Group &g) {
             if (this!=&g) {
                 delete [] this->participants;
                 copy(g);
             }
             return *this;
         }

        virtual void addParticipant(User &u) {
             for (int i=0; i<this->numOfParticipants; i++)
                 if (this->participants[i]==u) return;

             User *tmp=new User[this->numOfParticipants+1];
             for (int i=0; i<this->numOfParticipants; i++) tmp[i]=this->participants[i];
             tmp[this->numOfParticipants]=u;
             delete [] this->participants;
             this->participants=tmp;
             this->numOfParticipants++;
        }

        double getAverage() const {
             if (this->numOfParticipants==0) return 0;

             double sum=0;
             for (int i=0; i<this->numOfParticipants; i++)
                 sum+=this->participants[i].getPosition();

             return sum/this->numOfParticipants;
        }

        double rating() const {
             return (10-getAverage())*this->numOfParticipants/100.0;
        }

        friend ostream &operator<<(ostream &os, const Group &g);

        ~Group() {
             delete [] this->participants;
        }
};

ostream &operator<<(ostream &os, const Group &g) {
    os << "Group Name: " << g.groupName << "\nMember count: " << g.numOfParticipants << "\nRating: " << g.rating() << "\nMembers: " << '\n';
    for (int i=0; i<g.numOfParticipants; i++) os << i+1 << ") " << g.participants[i] << '\n';
    return os;
}

class PrivateGroup : public Group {
     public:
        static int capacity;
        static const float coefficient;

        PrivateGroup(const char *groupName) : Group(groupName) {}

        PrivateGroup(const PrivateGroup &pg) : Group(pg) {}

        PrivateGroup &operator=(const PrivateGroup &pg) {
            if (this!=&pg) Group::operator=(pg);
            return *this;
        }

        void addMember(User &u) {
            if (this->numOfParticipants==this->capacity) return;
            Group::addParticipant(u);
        }

        double rating() const {
            return (10-getAverage()) * (double(numOfParticipants)/this->capacity) * this->coefficient;
        }

         static void setCapacity(int c) {
            capacity=c;
        }

        static int getCapacity() {
            return capacity;
        }

        friend ostream &operator<<(ostream &os, const PrivateGroup &pg);
};

ostream &operator<<(ostream &os, const PrivateGroup &pg) {
    os << "Private Group: ";
    os << static_cast<const Group&>(pg);
    return os;
}

int PrivateGroup::capacity=10;
const float PrivateGroup::coefficient=0.8f;

int main() {
    cout << "INTEGRATION TEST" << '\n';
    char name[50];
    int nGroups;
    cin >> nGroups;

    Group **groups = new Group *[nGroups];
    for (int i = 0; i < nGroups; i++) {
        int type;
        cin >> type;
        cin >> name;
        if (type == 1) { //normal group
            groups[i] = new Group(name);
        } else { //private group
            groups[i] = new PrivateGroup(name);
        }
        int nUsers;
        cin >> nUsers;
        for (int j = 0; j < nUsers; j++) {
            User u;
            cin >> u;
            groups[i]->addParticipant(u);
        }
    }

    cout << "BEFORE CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i)
        cout << *groups[i];

    PrivateGroup::setCapacity(15);
    cout << "AFTER CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i)
        cout << *groups[i];

    return 0;
}