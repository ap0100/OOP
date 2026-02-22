#include <cstring>
#include <iostream>
using namespace std;

class QuizAttempt {
    char studentID[6];

    public:
        QuizAttempt(const char *id) {
            strcpy(this->studentID, id);
        }

        virtual double score() = 0;
        virtual void print() = 0;

        bool operator>=(QuizAttempt &a) {
            return this->score()>=a.score();
        }
};

class MCQuizAttempt : public QuizAttempt {
    char correctAnswers[10];
    char studentAnswers[10];

    public:
        MCQuizAttempt(char *id, const char *correct, const char *answers) : QuizAttempt(id) {
            strcpy(correctAnswers, correct);
            strcpy(studentAnswers, answers);
        }

        double score() {
            double total=0;
            for (int i=0; i<10; i++) {
                if (this->correctAnswers[i]==this->studentAnswers[i]) total++;
                else total-=0.25;
            }

            return total;
        }

        void print() {
            for (int i=0; i<10; i++) {
                cout << "Correct: " << this->correctAnswers[i] <<
                    " Answer: " << this->studentAnswers[i] <<
                    " Points:" << (this->correctAnswers[i]==this->studentAnswers[i] ? 1 : -0.25) << '\n';
            }

            cout << "Total score: " << this->score() << '\n';
        }

        ~MCQuizAttempt() {}
};

class TFQuizAttempt : public QuizAttempt {
    bool correct[10];
    bool answers[10];

    public:
        TFQuizAttempt(char *id, bool *correct, bool *canswers) : QuizAttempt(id) {
            for (int i=0; i<10; i++) {
                this->correct[i] = correct[i];
                this->answers[i] = canswers[i];
            }
        }

        double score() {
            double total=0;
            for (int i=0; i<10; i++) {
                if (this->correct[i]==this->answers[i]) total++;
                else total-=0.5;
            }

            return total;
        }

        void print() {
            for (int i=0; i<10; i++) {
                cout << "Correct: " << (this->correct[i]==1 ? "True" : "False") <<
                    " Answer: " << (this->answers[i]==1 ? "True" : "False") <<
                    " Points: " << (this->correct[i]==this->answers[i] ? 1 : -0.5) << '\n';
            }
            cout << "Total score: " << this->score() << '\n';
        }

        ~TFQuizAttempt() {}
};

double averagePointsOfPassedStudents (QuizAttempt ** attempts, int n) {
    double sum=0;
    int count=0;

    for (int i=0; i<n; i++) {
        if (attempts[i]->score()>=5.0) {
            sum+=attempts[i]->score();
            count++;
        }
    }

    if (count==0) return 0;
    return sum/count;
}

QuizAttempt *readMCQuizAttempt() {
    char ID[7];
    string correctStr, answersStr;
    cin >> ID >> correctStr >> answersStr;
    return new MCQuizAttempt(ID, correctStr.c_str(), answersStr.c_str());
}

QuizAttempt *readTFQuizAttempt() {
    char ID[7];
    cin >> ID;

    int tempCorrect[10];
    int tempAnswers[10];
    bool correct[10];
    bool answers[10];

    for (int i = 0; i < 10; i++) cin >> tempCorrect[i];
    for (int i = 0; i < 10; i++) cin >> tempAnswers[i];

    for (int i = 0; i < 10; i++) {
        correct[i] = (tempCorrect[i] != 0);
        answers[i] = (tempAnswers[i] != 0);
    }

    return new TFQuizAttempt(ID, correct, answers);
}


int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "Test MCQuizAttempt" << '\n';
        QuizAttempt *attempt = readMCQuizAttempt();
        cout << "Score: " << attempt->score() << '\n';
        attempt->print();
    } else if (testCase == 2) {
        cout << "Test TFQuizAttempt" << '\n';
        QuizAttempt *attempt = readTFQuizAttempt();
        cout << "Score: " << attempt->score() << '\n';
        attempt->print();
    } else if (testCase == 3) {
        cout << "Test operator >=" << '\n';
        int n;
        cin >> n;
        
        QuizAttempt **attempts = new QuizAttempt *[n];
        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;

            if (type == 1) attempts[i] = readMCQuizAttempt();
            else attempts[i] = readTFQuizAttempt();
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if ((*attempts[i]) >= (*attempts[j])) cout << i << " >= " << j << '\n';
                    else cout << i << " < " << j << '\n';
                }
            }
        }
    } else {
        int n;
        cin >> n;

        QuizAttempt **attempts = new QuizAttempt *[n];
        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;
            if (type == 1) attempts[i] = readMCQuizAttempt();
            else attempts[i] = readTFQuizAttempt();
            attempts[i]->print();
            cout << '\n';
        }

        for (int i = 0; i < n; i++) {
            attempts[i]->print();
            cout << '\n';
        }

        cout << "Average score of passed students is: " << averagePointsOfPassedStudents(attempts, n) << '\n';

        for (int i = 0; i < n; i++) delete attempts[i];
        delete [] attempts;
    }


    return 0;
}