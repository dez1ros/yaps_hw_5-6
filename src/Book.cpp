#include "Book.h"
#include <iostream>

Book::Book(std::string t, std::string a, int y, std::string i, bool available, std::string borrowed, time_t take, time_t ret)
    : title(t), author(a), year(y), isbn(i), isAvailable(available), borrowedBy(borrowed), takeDate(take), returnDate(ret)
{
    if (y <= 1450 || y >= 2025) {
        throw std::invalid_argument("Год издания должен быть между 1450 и 2025.");
    }
    if (i.empty()) {
        throw std::invalid_argument("ISBN не может быть пустым.");
    }
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

std::string Book::getISBN() const {
    return isbn;
}

bool Book::getAvailability() const {
    return isAvailable;
}

std::string Book::getBorrowedBy() const {
    return borrowedBy;
}

time_t Book::getTakeDate() const {
    return takeDate;
}

time_t Book::getReturnDate() const {
    return returnDate;
}

void Book::borrowBook(const std::string& userName, const int daysLimit) {
    if (isAvailable) {
        takeDate = std::time(0);
        returnDate = takeDate + daysLimit * 24 * 60 * 60;
        isAvailable = false;
        borrowedBy = userName;
        std::cout << "Книга \"" << title << "\" успешно взята пользователем " << userName << ".\n";
    } else {
        std::cout << "Книга \"" << title << "\" в данный момент недоступна.\n";
    }
}

void Book::returnBook() {
    if (!isAvailable) {
        isAvailable = true;
        std::cout << "Книга \"" << title << "\" успешно возвращена пользователем " << borrowedBy << ".\n";
        borrowedBy = "";
    } else {
        std::cout << "Книга \"" << title << "\" не была взята.\n";
    }
}

void Book::displayInfo() const {
    std::cout << "Информация о книге:\n";
    std::cout << "Название: " << title << "\n";
    std::cout << "Автор: " << author << "\n";
    std::cout << "Год издания: " << year << "\n";
    std::cout << "ISBN: " << isbn << "\n";
    if (!isAvailable) {
        std::cout << "Доступность: " << "Недоступна" << "\n";
        std::cout << "Взята пользователем: " << borrowedBy << "\n";
        std::cout << "Дата взятия: " << std::ctime(&takeDate);
        std::cout << "Дата возврата: " << std::ctime(&returnDate);
    } else 
    {
        std::cout << "Доступность: " << "Доступна" << "\n";
    }
}