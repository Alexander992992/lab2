#include "container.h"

Container::Container() : head(nullptr), tail(nullptr), count(0) {cout << "Вызван конструктор без параметров для класса Container\n";}

Container::Container(Node* h, Node* t, const int c) : head(h), tail(t), count(c) {
    cout << "Вызван конструктор с параметрами для класса Container\n";
}

Container::Container(const Container& other) : head(other.head), tail(other.tail), count(other.count) {
    cout << "Вызван конструктор копирования для класса Container\n";
}

Container::~Container() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
    }
    tail = nullptr;
    count = 0;
    cout << "Вызван деструктор для класса Container" << endl;
}


Node* Container::get_head() {
    return this->head;
}

Node* Container::get_tail() {
    return this->tail;
}

void Container::add_student(Student* St, int index) {
    if (index < 0 || index > count) {
        throw out_of_range("Индекс вне диапазона");
    }
    
    Node* node_to_add = new Node;
    node_to_add->data = St;
    node_to_add->next = nullptr;

    if (index == 0) {
        node_to_add->next = head;
        head = node_to_add;
        if (count == 0) {
            tail = node_to_add;
        }
    } else {
        Node* prev = head;
        for (int i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        node_to_add->next = prev->next;
        prev->next = node_to_add;
        
        if (node_to_add->next == nullptr) {
            tail = node_to_add;
        }
    }
    
    ++count;
}

Container& Container::delete_student(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Индекс вне диапазона");
    }

    Node* temp = head;

    if (index == 0) {
        head = head->next;
        delete temp->data;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        Node* prev = nullptr;
        for (int i = 0; i < index; ++i) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        if (temp == tail) {
            tail = prev;
        }
        delete temp->data;
        delete temp;
    }

    --count;
    return *this;
}

void Container::display_students() {
    Node* temp = head;
    if (count == 0) {
        cout << "Нет данных" << endl;
        return;
    }
    int index = 1;
    while (temp != 0) {
        cout << index << " - Студент:\n";
        temp->data->display_student();
        temp = temp->next;
        index++;
    }
}

void Container::sort_students_by_average_mark() {
    if (count < 2) return;

    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = head; j->next != nullptr; j = j->next) {
            if (j->data->get_average_mark() > j->next->data->get_average_mark()) {
                Student* temp = j->data;
                j->data = j->next->data;
                j->next->data = temp;
            }
        }
    }
}

void Container::search_students_with_failing_marks() {
    Node* temp = head;
    bool found = false;

    while (temp != nullptr) {
        Student* student = temp->data;
        const float* marks = student->get_marks();
        int size = student->get_size();

        for (int i = 0; i < size; i++) {
            if (marks[i] < 3.0f) {
                cout << "Студент с номером группы " << student->get_number()
                     << " и именем " << student->get_name()
                     << " имеет хотя бы одну неудовлетворительную оценку." << endl;
                found = true;
                break;
            }
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Студентов с неудовлетворительными оценками не найдено." << endl;
    }
}


Container& Container::edit_student(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Индекс вне диапазона");
    }

    Node* temp = head;
    for (int i = 0; i < index; ++i) {
        temp = temp->next;
    }

    temp->data->edit_student();
    return *this;
}

Container& Container::operator[](int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Индекс вне диапазона");
    }

    Node* temp = head;
    for (int i = 0; i < index; ++i) {
        temp = temp->next;
    }

    return *this;
}