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

void Library::borrowBook(const std::string& userName, const std::string& isbn, const int daysLimit) {
    User* user = findUserByName(userName);
    Book* book = findBookByISBN(isbn);

    if (user && book) {
        if (user->canBorrowMore() && book->getAvailability()) {
            book->borrowBook(userName, daysLimit);
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
            if (std::time(0) > book->getReturnDate()) {
                int overdueDays = (std::time(0) - book->getReturnDate()) / (24 * 60 * 60);
                int fineAmount = overdueDays;
                user->addFine(fineAmount);
                std::cout << "Книга возвращена с опозданием на " << overdueDays << " дней. Штраф: " << fineAmount << " единиц.\n";
            }
            else {
                std::cout << "Книга возвращена вовремя. Штрафов нет.\n";
            }
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

std::vector<Book*> Library::findBooksByAuthor(const std::string& author) {
    std::vector<Book*> authorBooks;
    for (auto& book : books) {
        if (book.getAuthor() == author) {
            authorBooks.push_back(&book);
        }
    }
    if (authorBooks.empty()) {
        throw std::invalid_argument("Книга с автором " + author + " не найдена в библиотеке.");
    }
    return authorBooks;
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

void Library::displayAllBooksSortedByYear() const {
    std::vector<Book> sortedBooks;
    std::vector<Book> tempBooks = books;
    int index = -1;
    while (true) {
        int minYear = 2026;
        for (size_t i = 0; i < tempBooks.size(); ++i) {
            if (tempBooks[i].getYear() < minYear) {
                minYear = tempBooks[i].getYear();
                index = i;
            }
        }
        sortedBooks.push_back(tempBooks[index]);
        tempBooks.erase(tempBooks.begin() + index);
        if (sortedBooks.size() == books.size()) {
            break;
        }
    }

    for (const auto& sortedBook : sortedBooks) {
        sortedBook.displayInfo();
        std::cout << "---------------------\n";
    }
    std::cout << "Все книги отсортированы по году издания.\n";
}

void Library::displayAllUsers() const {
    for (const auto& user : users) {
        user.displayProfile();
        std::cout << "---------------------\n";
    }
}

void Library::saveToFile() const {
    std::ofstream outFile(dataFile);
    if (!outFile) {
        throw std::invalid_argument("Не удалось открыть файл для записи!");
    }

    for (const auto& book : books) {
        outFile << "BOOK\n";
        outFile << "Title: " << book.getTitle() << "\n";
        outFile << "Author: " << book.getAuthor() << "\n";
        outFile << "Year: " << book.getYear() << "\n";
        outFile << "ISBN: " << book.getISBN() << "\n";
        outFile << "Available: " << (book.getAvailability() ? "yes" : "no") << "\n";
        outFile << "BorrowedBy: " << book.getBorrowedBy() << "\n";
        outFile << "TakeDate: " << book.getTakeDate() << "\n";
        outFile << "ReturnDate: " << book.getReturnDate() << "\n\n";
    }

    outFile << "---USERS---\n\n";

    for (const auto& user : users) {
        outFile << "USER\n";
        outFile << "Name: " << user.getName() << "\n";
        outFile << "UserID: " << user.getUserId() << "\n";
        outFile << "BorrowedBooks: ";
        const auto& borrowedBooks = user.getBorrowedBooks();
        for (size_t i = 0; i < borrowedBooks.size(); ++i) {
            outFile << borrowedBooks[i];
            if (i < borrowedBooks.size() - 1) {
                outFile << "|";
            }
        }
        outFile << "\n";
        outFile << "MaxBooks: " << user.getMaxBooksAllowed() << "\n";
        outFile << "FinesAmount: " << user.getFinesAmount() << "\n\n";
    }

    outFile << "---END---\n";

    outFile.close();

    std::cout << "Данные сохранены в файл.\n";

}

void Library::loadFromFile() {
    std::ifstream inFile(dataFile);

    if (!inFile) {
        inFile.close();
        std::ofstream out(dataFile);

        if (!out) {
            throw std::invalid_argument("Не удалось создать файл!");
        }

        out << "---END---\n";

        out.close();

        inFile.open(dataFile);
    }

    std::string line;

    std::string title, author, isbn, borrowedBy;
    std::time_t takeDate, returnDate;
    std::string name, userId, available;
    std::vector<std::string> borrowedBooks;
    std::string borrowedBooksLine;
    int year, maxBooks, fineAmount;

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

            std::getline(inFile, line);
            takeDate = std::stoi(deleteBackSymb(line.substr(10)));
            std::getline(inFile, line);
            returnDate = std::stoi(deleteBackSymb(line.substr(12)));

            Book book(title, author, year, isbn, (available.find("yes") == 0), borrowedBy, takeDate, returnDate);
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
            
            std::getline(inFile, line);
            fineAmount = std::stoi(deleteBackSymb(line.substr(12)));

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

            User user(name, userId, borrowedBooks, maxBooks, fineAmount);
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