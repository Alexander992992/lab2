#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class Student {
    private:
        string name;
        int number;
        string* subjects;
        float* marks;
        int size;
    public:
        Student();
        Student(const string& n, const int& num, const string* s, const float* m, const int& siz);
        Student(const Student& other);
        ~Student();

        string get_name() const;
        void set_name(const string& n);

        int get_number() const;
        void set_number(const int& n);

        const string* get_subjects() const;
        void set_subjects(const string* s, int siz);

        const float* get_marks() const;
        void set_marks(const float* m, int siz);

        int get_size() const;
        void set_size(const int& size);

        void display_student();
        void edit_student();
        float get_average_mark() const;
};