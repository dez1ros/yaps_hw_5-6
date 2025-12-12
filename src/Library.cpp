#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Library.h"

std::string deleteBackSymb(std::string line);

Library::Library(std::string filePath) : dataFile("../data/" + filePath) {
    loadFromFile();
}

Library::Library() {}

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
            throw std::invalid_argument("Невозможно взять книгу: либо пользователь достиг лимита, либо книга недоступна.\n");
        }
    } else {
        throw std::invalid_argument("Пользователь или книга не найдены.\n");
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
        throw std::invalid_argument("Книга не найдена или не была взята.\n");
    }
}

Book* Library::findBookByISBN(const std::string& isbn) {
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            return &book;
        }
    }
    throw std::invalid_argument("Книга с ISBN " + isbn + " не найдена в библиотеке.");
}

User* Library::findUserByName(const std::string& name) {
    for (auto& user : users) {
        if (user.getName() == name) {
            return &user;
        }
    }
    throw std::invalid_argument("Пользователь " + name + " не найден в библиотеке.");
}

std::vector<User> Library::getAllUsers() const {
    return users;
}

std::vector<std::string> Library::getAllIsbns() {
    std::vector<std::string> isbns = {};
    for (const auto& book : books) {
        isbns.push_back(book.getISBN());
    }
    return isbns;
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
        inFile.close();
        std::ofstream out(dataFile);

        if (!out) {
            throw std::invalid_argument("Ошибка: не удалось создать файл!");
        }

        out << "---END---\n";

        out.close();

        inFile.open(dataFile);
    }

    std::string line;

    std::string title, author, isbn, borrowedBy;
    std::string name, userId, available;
    std::vector<std::string> borrowedBooks;
    std::string borrowedBooksLine;
    int year, maxBooks;

    int count = 0;    
    while (1) {
        std::getline(inFile, line);
        if (line.find("BOOK") == 0) {
            std::getline(inFile, line);
            title = deleteBackSymb(line.substr(7));
            std::getline(inFile, line);
            author = deleteBackSymb(line.substr(8));
            std::getline(inFile, line);
            year = std::stoi(deleteBackSymb(line.substr(6)));
            std::getline(inFile, line);
            isbn = deleteBackSymb(line.substr(6));
            std::getline(inFile, line);
            available = deleteBackSymb(line.substr(11));
            std::getline(inFile, line);
            borrowedBy = deleteBackSymb(line.substr(12));
            
            for (const auto& book : books) {
                if (book.getISBN() == isbn) {
                    throw std::invalid_argument("Дублирование книги с ISBN " + isbn + " в файле");
                }
            }

            Book book(title, author, year, isbn, (available.find("yes") == 0), borrowedBy);
            addBook(book);

        } else if (line.find("USER") == 0) {

            std::getline(inFile, line);
            name = deleteBackSymb(line.substr(6));
            std::getline(inFile, line);
            userId = deleteBackSymb(line.substr(8));                        
            std::getline(inFile, line);
            borrowedBooksLine = deleteBackSymb(line.substr(15));
            std::istringstream borrowedBooksLineSS(borrowedBooksLine);
            std::string isbn;
            borrowedBooks.clear();
            while (std::getline(borrowedBooksLineSS, isbn, '|')) {
                borrowedBooks.push_back(isbn);
            }
            std::getline(inFile, line);
            maxBooks = std::stoi(deleteBackSymb(line.substr(9)));
            
            if (!maxBooks){
                maxBooks = 3;
            }
            if (borrowedBooks.empty()) {
                borrowedBooks = {};
            }

            for (const auto& user : users) {
                if (user.getUserId() == userId) {
                    throw std::invalid_argument("Дублирование пользователя с ID " + userId + " в файле");
                }
            }

            User user(name, userId, borrowedBooks, maxBooks);
            addUser(user);
        } else if (line.find("---END---") == 0) {
            break;
        }
    }

    std::cout << "Загружено книг: " << books.size() << ", пользователей " << users.size() << " из файла.\n";

    inFile.close();
}

std::string deleteBackSymb(std::string line){
    while (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
        line.pop_back();
    }
    return line;
}