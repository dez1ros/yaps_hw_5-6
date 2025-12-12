#pragma once

#include <string>
#include <vector>

class User {
private:
    std::string name;
    std::string userId;  // вид "USR_001"
    std::vector<std::string> borrowedBooks;
    int maxBooksAllowed;
    int finesAmount;

public:
    User(std::string n, std::string id, std::vector<std::string> borrowed = {}, int maxBooks = 3, int fines = 0);

    std::string getName() const;
    std::string getUserId() const;
    std::vector<std::string> getBorrowedBooks() const;
    int getMaxBooksAllowed() const;
    int getFinesAmount() const;

    void addFine(int amount);
    bool canBorrowMore();
    void addBook(const std::string& isbn);
    void removeBook(const std::string& isbn);
    void displayProfile() const;
};
