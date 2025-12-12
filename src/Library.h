#pragma once

#include <string>
#include <vector>
#include "Book.h"
#include "User.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;
    std::string dataFile;
public:
    Library();
    Library(std::string filePath);

    void addBook(const Book& book);
    void addUser(const User& user);

    void borrowBook(const std::string& userName, const std::string& isbn);
    void returnBook(const std::string& isbn);

    Book* findBookByISBN(const std::string& isbn);
    User* findUserByName(const std::string& name);

    std::vector<User> getAllUsers() const;
    std::vector<std::string> getAllIsbns();
    void displayAllBooks() const;
    void displayAllUsers() const;
    void saveToFile() const;
    void loadFromFile();
};