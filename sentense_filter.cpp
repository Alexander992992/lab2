#include "sentense_filter.h"

SentenceFilter::SentenceFilter() : source(""), isTextSource(false) {
    cout << "Default constructor called for class SentenceFilter\n";
}

SentenceFilter::SentenceFilter(const string& filename)
    : source(filename), isTextSource(false) {
    cout << "Constructor with parameters called for class SentenceFilter\n";
}

SentenceFilter::SentenceFilter(const string& text, bool isText)
    : source(text), isTextSource(isText) {
    cout << "Constructor with parameters called for class SentenceFilter\n";
}

SentenceFilter::SentenceFilter(const SentenceFilter& other)
    : source(other.source), isTextSource(other.isTextSource) {
    cout << "Copy constructor called for class SentenceFilter\n";
}

SentenceFilter::~SentenceFilter() {
    cout << "Destructor called for class SentenceFilter\n";
}


void SentenceFilter::result() const {
    string text;

    if (isTextSource) {
        text = source;
    } else {
        ifstream file(source);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << source << endl;
            return;
        }
        ostringstream buffer;
        buffer << file.rdbuf();
        text = buffer.str();
        file.close();
    }

    cout << "Read text:\n" << text << "\n\n";

    string* lines = nullptr;
    int lineCount = 0;
    split_into_lines(text, lines, lineCount);

    cout << "Lines containing two-digit numbers:\n";
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
