#include "container.h"
#include "student.h"
#include "check.h"
#include "sentense_filter.h"

void display_menu() {
    cout << "\n===== Меню управления студентами =====" << endl;
    cout << "1. Добавить студента" << endl;
    cout << "2. Удалить студента" << endl;
    cout << "3. Редактировать данные студента" << endl;
    cout << "4. Показать всех студентов" << endl;
    cout << "5. Сортировать по среднему баллу" << endl;
    cout << "6. Показать студентов с неудовлетворительными оценками" << endl;
    cout << "0. Выход" << endl;
    cout << "Введите ваш выбор: ";
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
                cout << "Введите имя студента: ";
                getline(cin, name);
                cout << "Введите номер группы студента: ";
                number = check_input();
                cout << "Введите количество предметов: ";
                size = check_input();

                string* subjects = new string[size];
                float* marks = new float[size];

                cout << "Введите названия предметов: ";
                for (int i = 0; i < size; i++) {
                    cin >> subjects[i];
                }

                cout << "Введите оценки: ";
                for (int i = 0; i < size; i++) {
                    cin >> marks[i];
                }

                cout << "Введите индекс для добавления студента: ";
                int index = check_input();

                Student* new_student = new Student(name, number, subjects, marks, size);
                students.add_student(new_student, index - 1);
                cout << "Студент добавлен." << endl;

                delete[] subjects;
                delete[] marks;
                break;
            }
            case 2: {
                int index;
                cout << "Введите индекс студента для удаления: ";
                index = check_input();
                try {
                    students.delete_student(index - 1);
                    cout << "Студент удален." << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 3: {
                int index;
                cout << "Введите индекс студента для редактирования: ";
                index = check_input();
                try {
                    students.edit_student(index - 1);
                    cout << "Данные студента обновлены." << endl;
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
                cout << "Выход из программы." << endl;
                return 0;
            }
            default: {
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
            }
        }
    }

    return 0;
}

int words_program() {
    try {
        int choice;
        cout << "Выберите источник (1 - текстовая строка, 2 - файл): ";
        if (!(cin >> choice)) {
            throw invalid_argument("Ошибка: Неверный ввод для выбора источника.");
        }

        if (choice == 1) {
            cin.ignore();
            char text[8192];
            cout << "Введите текст: ";
            cin.getline(text, sizeof(text));

            if (cin.fail()) {
                throw overflow_error("Ошибка: Превышена максимальная длина текста.");
            }

            SentenceFilter filter(text, true);
            filter.result();
        } else if (choice == 2) {
            char filename[256];
            cout << "Введите имя файла: ";
            cin >> filename;
            ifstream file(filename);
            if (!file) {
                throw runtime_error("Ошибка: Файл не найден или не может быть открыт.");
            }
            file.close();
            SentenceFilter filter(filename);
            filter.result();
        } else {
            throw out_of_range("Ошибка: Выбранный источник не существует.");
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
        cerr << "Произошла неизвестная ошибка." << endl;
        return -1;
    }
    return 0;
}

int main() {
    int choice;
    while (true) {
        cout << "Выберите тип задачи:" << endl;
        cout << "1 - Стандартные потоки" << endl;
        cout << "2 - Файловые и текстовые потоки" << endl;
        cout << "3 - Выход" << endl;
        choice = check_input();

        switch (choice) {
            case 1:
                students_program();
                break;
            case 2:
                words_program();
                break;
            case 3:
                cout << "Выход." << endl;
                return 0;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
        }
    }
}