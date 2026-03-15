#pragma execution_character_set("utf-8")
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

enum Speciality { CS, INF, ME, FI, TN };

struct Student {
    string surname;
    int course;
    Speciality speciality;
    int physics;
    int math;
    int informatics;
};

int utf8_length(const string& str) {
    int len = 0;
    for (char c : str)
        if ((c & 0xC0) != 0x80) len++;
    return len;
}

double Avg(Student s) {
    return (s.physics + s.math + s.informatics) / 3.0;
}

void Create(Student* p, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент № " << i + 1 << endl;

        cout << "Прізвище: ";
        cin >> ws;
        getline(cin, p[i].surname);

        cout << "Курс: ";
        cin >> p[i].course;

        cout << "Спеціальність (0-CS 1-INF 2-ME 3-FI 4-TN): ";
        int s;
        cin >> s;
        p[i].speciality = (Speciality)s;

        cout << "Фізика: ";
        cin >> p[i].physics;

        cout << "Математика: ";
        cin >> p[i].math;

        cout << "Інформатика: ";
        cin >> p[i].informatics;
    }
}

void Print(Student* p, const int N) {

    cout << "\n====================================================================\n";
    cout << "| № | Прізвище     | Курс | Фізика | Математика | Інформатика |\n";
    cout << "--------------------------------------------------------------------\n";

    for (int i = 0; i < N; i++) {

        cout << "| " << setw(2) << i + 1 << " | ";

        int spaces = 13 - utf8_length(p[i].surname);
        cout << p[i].surname << string(spaces > 0 ? spaces : 0, ' ') << " | ";

        cout << setw(4) << p[i].course << " | ";
        cout << setw(6) << p[i].physics << " | ";
        cout << setw(10) << p[i].math << " | ";
        cout << setw(11) << p[i].informatics << " |\n";
    }

    cout << "====================================================================\n";
}

void Sort(Student* p, int N) {
    Student tmp;

    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - i - 1; j++) {

            if (p[j].informatics > p[j + 1].informatics ||
                (p[j].informatics == p[j + 1].informatics &&
                    Avg(p[j]) > Avg(p[j + 1])) ||
                (p[j].informatics == p[j + 1].informatics &&
                    Avg(p[j]) == Avg(p[j + 1]) &&
                    p[j].surname > p[j + 1].surname)) {

                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
}

int BinarySearch(Student* p, int N, string surname, double avg, int mark) {

    int L = 0;
    int R = N - 1;

    while (L <= R) {

        int m = (L + R) / 2;

        if (p[m].surname == surname &&
            Avg(p[m]) == avg &&
            p[m].informatics == mark)
            return m;

        if (p[m].informatics < mark)
            L = m + 1;
        else
            R = m - 1;
    }

    return -1;
}

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    {
        setlocale(LC_ALL, "uk_UA.UTF-8");
    }

    int N;

    cout << "Кількість студентів: ";
    cin >> N;

    Student* p = new Student[N];

    Create(p, N);

    Print(p, N);

    Sort(p, N);

    cout << "\nПісля сортування:\n";
    Print(p, N);

    string s;
    double avg;
    int mark;

    cout << "\nПошук студента\n";
    cout << "Прізвище: ";
    cin >> s;

    cout << "Середній бал: ";
    cin >> avg;

    cout << "Оцінка з інформатики: ";
    cin >> mark;

    int k = BinarySearch(p, N, s, avg, mark);

    if (k >= 0)
        cout << "Студент знайдений\n";
    else
        cout << "Студента немає\n";

    delete[] p;

    return 0;
}