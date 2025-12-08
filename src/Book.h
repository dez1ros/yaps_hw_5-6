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
    Book(std::string t, std::string a, int y, std::string i, bool available = true, std::string borrowed = "");

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
