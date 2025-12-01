#include "Library.h"
#include <iostream>
#include <fstream>

Library::Library(const std::string& filePath) : dataFile(filePath) {
    loadFromFile();
}

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::addUser(const User& user) {
    users.push_back(user);
}

void Library::borrowBook(const std::string& userName, const std::string& isbn) {
    User* user = findUserByName(userName);
    Book* book = findBookByISBN(isbn);

    if (user && book) {
        if (user->canBorrowMore() && book->getAvailability()) {
            book->borrowBook(userName);
            user->addBook(isbn);
        } else {
            std::cout << "Невозможно взять книгу: либо пользователь достиг лимита, либо книга недоступна.\n";
        }
    } else {
        std::cout << "Пользователь или книга не найдены.\n";
    }
}

void Library::returnBook(const std::string& isbn) {
    Book* book = findBookByISBN(isbn);
    if (book && !book->getAvailability()) {
        User* user = findUserByName(book->getBorrowedBy());
        if (user) {
            book->returnBook();
            user->removeBook(isbn);
        }
    } else {
        std::cout << "Книга не найдена или не была взята.\n";
    }
}

Book* Library::findBookByISBN(const std::string& isbn) {
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            return &book;
        }
    }
    return nullptr;
}

User* Library::findUserByName(const std::string& name) {
    for (auto& user : users) {
        if (user.getName() == name) {
            return &user;
        }
    }
    return nullptr;
}

void Library::displayAllBooks() const {
    for (const auto& book : books) {
        book.displayInfo();
        std::cout << "---------------------\n";
    }
}

void Library::displayAllUsers() const {
    for (const auto& user : users) {
        user.displayProfile();
        std::cout << "---------------------\n";
    }
}

void Library::saveToFile() const {
    // Реализация сохранения данных в файл
}

void Library::loadFromFile() {
    std::ifstream inFile(dataFile);
    if (!inFile) {
        std::cout << "Не удалось открыть файл для загрузки данных: " << dataFile << "\n";
        return;
    }

    
    
}