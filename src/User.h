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
    User(std::string n, std::string id, std::vector<std::string> borrowed = {}, int maxBooks = 3);

    std::string getName() const;
    std::string getUserId() const;
    std::vector<std::string> getBorrowedBooks() const;
    int getMaxBooksAllowed() const;

    bool canBorrowMore();
    void addBook(const std::string& isbn);
    void removeBook(const std::string& isbn);
    void displayProfile() const;
};
