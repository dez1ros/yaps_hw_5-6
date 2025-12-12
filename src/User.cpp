#include "User.h"
#include <iostream>
#include <algorithm>

User::User(std::string n, std::string id, std::vector<std::string> borrowed, int maxBooks, int fines)
    : name(n), userId(id), borrowedBooks(borrowed), maxBooksAllowed(maxBooks), finesAmount(fines) {}

std::string User::getName() const {
    return name;
}

std::string User::getUserId() const {
    return userId;
}

std::vector<std::string> User::getBorrowedBooks() const {
    return borrowedBooks;
}

int User::getMaxBooksAllowed() const {
    return maxBooksAllowed;
}

bool User::canBorrowMore() {
    return borrowedBooks.size() < maxBooksAllowed;
}

int User::getFinesAmount() const {
    return finesAmount;
}

void User::addFine(int amount) {
    finesAmount += amount;
}

void User::addBook(const std::string& isbn) {
    if (canBorrowMore()) {
        borrowedBooks.push_back(isbn);
    } else {
        std::cout << "Пользователь " << name << " достиг максимального лимита взятых книг " << maxBooksAllowed << ".\n";
    }
}

void User::removeBook(const std::string& isbn) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    } else {
        std::cout << "Книга с ISBN " << isbn << " не найдена в списке взятых книг пользователя " << name << ".\n";
    }
}

void User::displayProfile() const {
    std::cout << "Профиль пользователя:\n";
    std::cout << "Имя: " << name << "\n";
    std::cout << "ID пользователя: " << userId << "\n";
    std::cout << "Взятые книги (ISBN): ";
    for (size_t i = 0; i < borrowedBooks.size(); ++i) {
        std::cout << borrowedBooks[i];
        if (i < borrowedBooks.size() - 1) {
            std::cout << "|";
        }
    }
    std::cout << "\nМаксимальное количество книг: " << maxBooksAllowed << "\n";
    std::cout << "Сумма штрафов: " << finesAmount << "\n";
}

