#include "container.h"
#include "student.h"
#include "check.h"
#include "sentense_filter.h"

void display_menu() {
    cout << "\n===== Student Management Menu =====" << endl;
    cout << "1. Add a student" << endl;
    cout << "2. Remove a student" << endl;
    cout << "3. Edit student data" << endl;
    cout << "4. Display all students" << endl;
    cout << "5. Sort by average mark" << endl;
    cout << "6. Show students with at least one failing grade" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int students_program() {
    Container students;
    int choice;

    while (true) {
        display_menu();
        choice = check_input();

        switch (choice) {
            case 1: {
                string name;
                int number, size;
                cout << "Enter student's name: ";
                getline(cin, name);
                cout << "Enter student's number of the group: ";
                number = check_input();
                cout << "Enter the number of subjects: ";
                size = check_input();

                string* subjects = new string[size];
                float* marks = new float[size];

                cout << "Enter subject names: ";
                for (int i = 0; i < size; i++) {
                    cin >> subjects[i];
                }

                cout << "Enter marks: ";
                for (int i = 0; i < size; i++) {
                    cin >> marks[i];
                }

                cout << "Enter the student's index to add: ";
                int index = check_input();

                Student* new_student = new Student(name, number, subjects, marks, size);
                students.add_student(new_student, index - 1);
                cout << "Student added." << endl;

                delete[] subjects;
                delete[] marks;
                break;
            }
            case 2: {
                int index;
                cout << "Enter the index of the student to remove: ";
                index = check_input();
                try {
                    students.delete_student(index - 1);
                    cout << "Student removed." << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 3: {
                int index;
                cout << "Enter the index of the student to edit: ";
                index = check_input();
                try {
                    students.edit_student(index - 1);
                    cout << "Student data updated." << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 4: {
                students.display_students();
                break;
            }
            case 5: {
                students.sort_students_by_average_mark();
                students.display_students();
                break;
            }
            case 6: {
                students.search_students_with_failing_marks();
                break;
            }
            case 0: {
                cout << "Exiting the program." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice! Try again." << endl;
                break;
            }
        }
    }

    return 0;
}

int words_program() {
    try {
        int choice;
        cout << "Select a source (1 - text string, 2 - file): ";
        if (!(cin >> choice)) {
            throw invalid_argument("Error: Invalid input for source selection.");
        }

        if (choice == 1) {
            cin.ignore();
            char text[8192];
            cout << "Enter the text: ";
            cin.getline(text, sizeof(text));

            if (cin.fail()) {
                throw overflow_error("Error: Exceeded maximum text length.");
            }

            SentenceFilter filter(text, true);
            filter.result();
        } else if (choice == 2) {
            char filename[256];
            cout << "Enter the file name: ";
            cin >> filename;
            ifstream file(filename);
            if (!file) {
                throw runtime_error("Error: File not found or cannot be opened.");
            }
            file.close();
            SentenceFilter filter(filename);
            filter.result();
        } else {
            throw out_of_range("Error: Selected source does not exist.");
        }
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        return 1;
    }
    catch (const overflow_error& e) {
        cerr << e.what() << endl;
        return 2;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 3;
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
        return 4;
    }
    catch (...) {
        cerr << "An unknown error occurred." << endl;
        return -1;
    }
    return 0;
}

int main() {
    int choice;
    while (true) {
        cout << "Select task type:" << endl;
        cout << "1 - Standard streams" << endl;
        cout << "2 - File and text streams" << endl;
        cout << "3 - Exit" << endl;
        choice = check_input();

        switch (choice) {
            case 1:
                students_program();
                break;
            case 2:
                words_program();
                break;
            case 3:
                cout << "Exiting." << endl;
                return 0;
            default:
                cout << "Invalid choice! Try again." << endl;
                break;
        }
    }
}
