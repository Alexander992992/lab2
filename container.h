#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "student.h"

using namespace std;

struct Node
{
    Node* next;
    Student* data;
};

class Container
{
private:
    Node* head;
    Node* tail;
    int count;

public:
    Container();
    Container(Node* h, Node* t, const int c);
    Container(const Container& other);
    ~Container();

    Node* get_head();
    Node* get_tail();

    void add_student(Student* St, int index);
    Container& delete_student(int index);
    Container& edit_student(int index);
    void display_students();
    void sort_students_by_average_mark();
    void search_students_with_failing_marks();

    Container& operator[](int index);
};

