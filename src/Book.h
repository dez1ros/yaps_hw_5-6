#pragma once

#include <string>
#include <ctime>

class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string isbn;
    bool isAvailable;
    std::string borrowedBy;
    time_t takeDate;
    time_t returnDate;

public:
    Book(std::string t, std::string a, int y, std::string i, bool available = true, std::string borrowed = "", time_t take = 0, time_t ret = 0);

    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getISBN() const;
    bool getAvailability() const;
    std::string getBorrowedBy() const;
    time_t getTakeDate() const;
    time_t getReturnDate() const;

    void borrowBook(const std::string& userName, const int daysLimit);
    void returnBook();
    void displayInfo() const;
};
