#include <iostream>
#include "User.h"
#include "Book.h"
#include "Library.h"

User createUser(std::vector<User> users);
Book createBook();
void mainMenu();

int main() {
    system("clear");
    // setlocale(LC_ALL, "Russian");

    Library library("library_data.txt");

    while (1) {
        int choice;
        mainMenu();
        
        std::cin >> choice;
        system("clear");

        if (choice == 1){
            library.displayAllBooks();
        } else if (choice == 2){
            library.displayAllUsers();
        } else if (choice == 3){

            library.addBook(createBook());
        } else if (choice == 4){
            library.addUser(createUser(library.getAllUsers()));
        } else if (choice == 5){
            std::string userName, isbn;
            std::cout << "Введите ID пользователя: ";
            std::cin >> userName;
            std::cout << "Введите ISBN книги: ";
            std::cin >> isbn;
            library.borrowBook(userName, isbn);             
        } else if (choice == 6) {
            std::string isbn;
            std::cout << "Введите ISBN книги для возврата: ";
            std::cin >> isbn;
            library.returnBook(isbn);
        } else if (choice == 7) {
            std::string isbn;
            std::cout << "Введите ISBN книги для поиска: ";
            std::cin >> isbn;
            Book* book = library.findBookByISBN(isbn);
            if (book) {
                book->displayInfo();
            } else {
                std::cout << "Книга с ISBN " << isbn << " не найдена.\n";
            }
        } else if (choice == 8) {
            std::string userNameID;
            std::cout << "Введите ID пользователя для просмотра профиля: ";
            std::cin >> userNameID;
            User* user = library.findUserByName(userNameID);
            if (user) {
                std::cout << "---------------------\n";
                user->displayProfile();
                std::cout << "---------------------\n";
            } else {
                std::cout << "Пользователь " << userNameID << " не найден.\n";
            }
        } else if (choice == 9) {
            library.saveToFile();
            std::cout << "Данные сохранены в файл.\n";
        } else if (choice == 10) {
            std::cout << "Выход из программы.\n";
            break;
        } else {
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }

        std::cout << "\n" << "Нажмите Enter, чтобы продолжить...";
        
        std::cin.get();

        system("clear");

    }   

    return 0;
}


void mainMenu(){
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
}

Book createBook(){
    std::string title, author, isbn;
    int year;

    std::cout << "Введите название книги: ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, title);

    std::cout << "Введите автора книги: ";
    std::getline(std::cin, author);

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
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, name);
    
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