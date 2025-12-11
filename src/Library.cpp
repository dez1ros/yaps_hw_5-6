#include <iostream>
#include <fstream>
#include <sstream>
#include "Library.h"


Library::Library(std::string filePath) : dataFile("../data/" + filePath) {
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
        std::ofstream out(dataFile);

        if (!out) {
            std::cerr << "Ошибка: не удалось создать файл!" << std::endl;
            return;
        }

        out.close();
    }

    std::string line;

    std::string title, author, isbn, borrowedBy;
    std::string name, userId;
    std::vector<std::string> borrowedBooks;
    std::string borrowedBooksLine;
    int year, maxBooks;
    bool available;

    int count = 0;
    while (std::getline(inFile, line)) {
        if (line.find("BOOK") == 0) {
            std::getline(inFile, line);
            title = line.substr(7);
            std::getline(inFile, line);
            author = line.substr(8);
            std::getline(inFile, line);
            year = std::stoi(line.substr(6));
            std::getline(inFile, line);
            isbn = line.substr(6);
            std::getline(inFile, line);
            available = (line.substr(11) == "yes");
            std::getline(inFile, line);
            borrowedBy = line.substr(12);

            Book book(title, author, year, isbn, available, borrowedBy);
            addBook(book);

        } else if (line.find("USER") == 0) {

            std::getline(inFile, line);
            name = line.substr(6);
            std::getline(inFile, line);
            userId = line.substr(8);
            std::getline(inFile, line);
            borrowedBooksLine = line.substr(15);
            std::istringstream borrowedBooksLineSS(borrowedBooksLine);
            std::string isbn;
            borrowedBooks.clear();
            while (std::getline(borrowedBooksLineSS, isbn, '|')) {
                borrowedBooks.push_back(isbn);
            }
            std::getline(inFile, line);
            maxBooks = std::stoi(line.substr(9));
            
            if (!maxBooks){
                maxBooks = 3;
            }
            if (borrowedBooks.empty()) {
                borrowedBooks = {};
            }

            User user(name, userId, borrowedBooks, maxBooks);
            addUser(user);
        }
    }

    inFile.close();
}