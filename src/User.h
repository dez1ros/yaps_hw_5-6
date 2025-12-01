#pragma once

#include <string>
#include <vector>

class User {
private:
    std::string name;
    std::string userId;  // вид "USR_001"
    std::vector<std::string> borrowedBooks;
    int maxBooksAllowed;

public:
    User(const std::string& n, const std::string& id, const std::vector<std::string>& borrowed = {}, int maxBooks = 3)
        : name(n), userId(id), borrowedBooks(borrowed), maxBooksAllowed(maxBooks) {}

    std::string getName() const;
    std::string getUserId() const;
    std::vector<std::string> getBorrowedBooks() const;
    int getMaxBooksAllowed() const;

    bool canBorrowMore();
    void addBook(const std::string& isbn);
    void removeBook(const std::string& isbn);
    void displayProfile() const;
};
