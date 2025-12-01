#pragma once

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string isbn;
    bool isAvailable;
    std::string borrowedBy;

public:
    Book(const std::string& t, const std::string& a, const int y, const std::string& i, const bool available = true, const std::string& borrowed = "");

    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getISBN() const;
    bool getAvailability() const;
    std::string getBorrowedBy() const;
    

    void borrowBook(const std::string& userName);
    void returnBook();
    void displayInfo() const;
};
