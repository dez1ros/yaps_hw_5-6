#include <iostream>
#include "User.h"
#include "Book.h"
#include "Library.h"

User createUser(std::vector<User> users);
Book createBook();
int mainMenu();

int main() {
    Library library("library_data.txt");

    while (1) {
        int choice = mainMenu();

        if (choice == 1){
            library.displayAllBooks();
        } else if (choice == 2){
            library.displayAllUsers();
        } else if (choice == 3){
            library.addBook(createBook());
        } else if (choice == 4){
            library.addUser(createUser(library.getAllUsers()));
        } else if (choice == 5){
            std::cout << "Введите имя пользователя: ";
        }

        if (choice == 10) {
            library.saveToFile();
            std::cout << "Данные сохранены. Выход из программы.\n";
            break;
        }
    }   
        
    return 0;
}


int mainMenu(){
    int choice;

    std::cout << "=== БИБЛИОТЕКА ===\n";
    std::cout << "1. Просмотреть все книги\n";
    std::cout << "2. Просмотреть всех пользователей\n";
    std::cout << "3. Добавить новую книгу\n";
    std::cout << "4. Зарегистрировать пользователя\n";
    std::cout << "5. Выдать книгу пользователю\n";
    std::cout << "6. Принять книгу от пользователя\n";
    std::cout << "7. Поиск книги по ISBN\n";
    std::cout << "8. Просмотреть профиль пользователя\n";
    std::cout << "9. Сохранить данные в файл\n";
    std::cout << "10. Выход\n";

    std::cout << "Ваш выбор: ";

    std::cin >> choice;

    return choice;
}

Book createBook(){
    std::string title, author, isbn;
    int year;

    std::cout << "Введите название книги: ";
    std::cin >> title;

    std::cout << "Введите автора книги: ";
    std::cin >> author ;

    std::cout << "Введите год издания: ";
    std::cin >> year;

    std::cout << "Введите ISBN книги: ";
    std::cin >> isbn;

    Book newBook(title, author, year, isbn);
    return newBook;
}

User createUser(std::vector<User> users) {
    std::string name, lastUserId, userId;
    int maxID;

    std::cout << "Введите имя пользователя: ";
    std::cin >> name;
    
    if (users.empty()){
        lastUserId = "000";
    }
    else{
        for (const auto& user : users){
            if (user.getUserId().substr(4) > lastUserId){
                lastUserId = user.getUserId().substr(4);
            }
        }
    }
    userId = std::to_string(std::stoi(lastUserId) + 1);
    int zSize = 3 - userId.length();
    User newUser(name, "USR_" + std::string(zSize, '0') + userId);

    return newUser;
}