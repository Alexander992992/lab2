#include "student.h"

Student::Student() : name(""), number(0), subjects(nullptr), marks(nullptr), size(0) {
    cout << "Вызван конструктор без параметров для класса Student\n";
}

Student::Student(const string& n, const int& num, const string* s, const float* m, const int& siz)
    : name(n), number(num), size(siz) {
    subjects = new string[size];
    for (int i = 0; i < size; ++i) {
        subjects[i] = s[i];
    }
    marks = new float[size];
    std::copy(m, m + size, marks);
    cout << "Вызван конструктор с параметрами для класса Student\n";
}


Student::Student(const Student& other) : name(other.name), number(other.number), size(other.size) {
    subjects = new string[size];
    for (int i = 0; i < size; ++i) {
        subjects[i] = other.subjects[i];
    }
    marks = new float[size];
    std::copy(other.marks, other.marks + size, marks);
    cout << "Вызван конструктор копирования для класса Student\n";
}


Student::~Student() {
     delete[] subjects;
    delete[] marks;
    cout << "Вызван деструктор для класса Student\n";
}

string Student::get_name() const{
    return this->name;
}

void Student::set_name(const string& n) {
    this->name = n;
}

int Student::get_number() const{
    return this->number;
}

void Student::set_number(const int& n) {
    this->number = n;
}

const string* Student::get_subjects() const { 
    return subjects; 
}

void Student::set_subjects(const string* s, int siz) {
    delete[] subjects;
    size = siz;
    subjects = new string[size];
    memcpy(subjects, s, size * sizeof(string));
}

const float* Student::get_marks() const { 
    return marks; 
}

void Student::set_marks(const float* m, int siz) {
    delete[] marks;
    size = siz;
    marks = new float[size];
    memcpy(marks, m, size * sizeof(float));
}

int Student::get_size() const { 
    return size; 
}

void Student::set_size(const int& siz) { 
    size = siz; 
}

void Student::display_student() {
    cout << "Имя: " << name << "\nНомер группы: " << number << "\nПредметы: ";
    for (int i = 0; i < size; i++) cout << subjects[i] << ' ';
    cout << "\nОценки: ";
    for (int i = 0; i < size; i++) cout << marks[i] << ' ';
    cout << endl;
}

void Student::edit_student() {
    int choice;
    cout << "Выберите, что хотите изменить:\n";
    cout << "1. Имя студента\n";
    cout << "2. Номер группы студента\n";
    cout << "3. Список предметов и оценок\n";
    cout << "Введите ваш выбор: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            string new_name;
            cout << "Введите новое имя студента: ";
            cin.ignore();
            getline(cin, new_name);
            set_name(new_name);
            break;
        }
        case 2: {
            int new_number;
            cout << "Введите новый номер группы студента: ";
            cin >> new_number;
            set_number(new_number);
            break;
        }
        case 3: {
            int new_size;
            cout << "Введите количество предметов: ";
            cin >> new_size;

            string* new_subjects = new string[new_size];
            cout << "Введите названия предметов: ";
            for (int i = 0; i < new_size; i++) {
                cin >> new_subjects[i];
            }

            set_subjects(new_subjects, new_size);
            float* new_marks = new float[new_size];
            cout << "Введите оценки: ";
            for (int i = 0; i < new_size; i++) {
                cin >> new_marks[i];
            }

            set_marks(new_marks, new_size);
            delete[] new_subjects;
            delete[] new_marks;
            break;
        }
        default:
            cout << "Неверный выбор!" << endl;
    }
}


float Student::get_average_mark() const {
    if (size == 0) return 0.0f;

    float sum = 0.0f;
    for (int i = 0; i < size; i++) {
        sum += marks[i];
    }
    return sum / size;
}