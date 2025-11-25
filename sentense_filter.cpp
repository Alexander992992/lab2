#include "sentense_filter.h"

SentenceFilter::SentenceFilter() : source(""), isTextSource(false) {
    cout << "Вызван конструктор по умолчанию для класса SentenceFilter\n";
}

SentenceFilter::SentenceFilter(const string& filename)
    : source(filename), isTextSource(false) {
    cout << "Вызван конструктор с параметрами для класса SentenceFilter\n";
}

SentenceFilter::SentenceFilter(const string& text, bool isText)
    : source(text), isTextSource(isText) {
    cout << "Вызван конструктор с параметрами для класса SentenceFilter\n";
}

SentenceFilter::SentenceFilter(const SentenceFilter& other)
    : source(other.source), isTextSource(other.isTextSource) {
    cout << "Вызван конструктор копирования для класса SentenceFilter\n";
}

SentenceFilter::~SentenceFilter() {
    cout << "Вызван деструктор для класса SentenceFilter\n";
}


void SentenceFilter::result() const {
    string text;

    if (isTextSource) {
        text = source;
    } else {
        ifstream file(source);
        if (!file.is_open()) {
            cerr << "Не удалось открыть файл: " << source << endl;
            return;
        }
        ostringstream buffer;
        buffer << file.rdbuf();
        text = buffer.str();
        file.close();
    }

    cout << "Прочитанный текст:\n" << text << "\n\n";

    string* lines = nullptr;
    int lineCount = 0;
    split_into_lines(text, lines, lineCount);

    cout << "Строки, содержащие двузначные числа:\n";
    for (int i = 0; i < lineCount; ++i) {
        if (contains_two_digit_number(lines[i])) {
            cout << lines[i] << endl;
        }
    }

    delete[] lines;
}

void SentenceFilter::split_into_lines(const string& text, string*& lines, int& lineCount) const {
    const int maxLines = 100;
    lines = new string[maxLines];
    lineCount = 0;
    istringstream stream(text);
    string line;

    while (getline(stream, line)) {
        if (lineCount < maxLines) {
            lines[lineCount++] = line;
        }
    }
}

bool SentenceFilter::contains_two_digit_number(const string& line) const {
    regex twoDigitRegex("\\b\\d{2}\\b");
    return regex_search(line, twoDigitRegex);
}