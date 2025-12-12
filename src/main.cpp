#include <iostream>
#include "User.h"
#include "Book.h"
#include "Library.h"

User createUser(std::vector<User> users);
Book createBook(std::vector<std::string> existingISBNs);
void mainMenu();
std::string deleteBackSymb(std::string line);

int main() {
    system("clear");
    Library library;

    try {
        library = Library("library_data.txt");
    } catch (const std::invalid_argument& e) {
        std::cout << "Ошибка при инициализации библиотеки: " << e.what() << std::endl;
        return 1;
    }
    
    int errFlag;

    while (1) {
        errFlag = 0;
        int choice;
        mainMenu();
        
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            choice = -1;
        }
        std::cin.ignore(1000, '\n');
        system("clear");

        if (choice == 1){
            std::cout << "---------------------------------------------------------------------------------------" << std::endl;
            library.displayAllBooks();
        } else if (choice == 2){
            std::cout << "---------------------------------------------------------------------------------------" << std::endl;
            library.displayAllUsers();
        } 
        else if (choice == 3){
            try {
                std::vector<std::string> existingISBNs = library.getAllIsbns();
                library.addBook(createBook(existingISBNs));
            } catch (const std::invalid_argument& e) {
                std::cout << "Ошибка при добавлении книги: " << e.what() << std::endl;
                errFlag = 1;
            }
        } 
        else if (choice == 4){
            try{
                library.addUser(createUser(library.getAllUsers()));
            } catch (const std::invalid_argument& e) {
                std::cout << "Ошибка при регистрации пользователя: " << e.what() << std::endl;
                errFlag = 1;
            }
        } 
        else if (choice == 5){
            std::string userName, isbn;
            std::cout << "Введите имя пользователя: ";
            std::cin >> userName;
            std::cout << "Введите ISBN книги: ";
            std::cin >> isbn;
            std::cin.ignore(1000, '\n');
            try{
                library.borrowBook(userName, isbn);    
            } catch (const std::invalid_argument& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
                errFlag = 1;
            }
        } 
        else if (choice == 6) {
            std::string isbn;
            std::cout << "Введите ISBN книги для возврата: ";
            std::cin >> isbn;
            std::cin.ignore(1000, '\n');
            try{
                library.returnBook(isbn);
            } catch (const std::invalid_argument& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
                errFlag = 1;
            }
        } 
        else if (choice == 7) {
            std::string isbn;
            std::cout << "Введите ISBN книги для поиска: ";
            std::cin >> isbn;
            std::cin.ignore(1000, '\n');

            Book* book;
            try{
                book = library.findBookByISBN(isbn);
            } catch (const std::invalid_argument& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
                errFlag = 1;
            }
            if (!errFlag) {
                std::cout << "---------------------\n";
                book->displayInfo();
                std::cout << "---------------------\n";
            }
        } 
        else if (choice == 8) {
            std::string userName;
            std::cout << "Введите имя пользователя для просмотра профиля: ";
            std::cin >> userName;
            std::cin.ignore(1000, '\n');

            User* user;
            try {
                user = library.findUserByName(userName);
                std::cout << "---------------------\n";
                user->displayProfile();
                std::cout << "---------------------\n";
            } catch (const std::invalid_argument& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
                errFlag = 1;
            }
        } 
        else if (choice == 9) {
            library.saveToFile();
            std::cout << "Данные сохранены в файл.\n";
        } 
        else if (choice == 10) {
            std::cout << "Выход из программы.\n";
            break;
        } 
        else {
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            errFlag = 1;
        }

        if (!errFlag){
            std::cout << "\nОперация выполнена успешно.\n";    
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

Book createBook(std::vector<std::string> existingISBNs) {
    std::string title, author, isbn;
    int year;

    std::cout << "Введите название книги: ";
    std::getline(std::cin, title);

    std::cout << "Введите автора книги: ";
    std::getline(std::cin, author);

    std::cout << "Введите год издания: ";
    std::cin >> year;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        throw std::invalid_argument("Некорректный год издания.");
    }

    std::cout << "Введите ISBN книги: ";
    std::cin >> isbn;
    std::cin.ignore(1000, '\n');

    for (auto& existingISBN : existingISBNs) {
        if (isbn == existingISBN) {
            throw std::invalid_argument("Книга с таким ISBN уже существует в библиотеке.");
        }
    }

    Book newBook(deleteBackSymb(title), deleteBackSymb(author), year, isbn);
    return newBook;
}

User createUser(std::vector<User> users) {
    std::string name, lastUserId, userId;
    int maxID;

    std::cout << "Введите имя пользователя: ";
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
    if (std::stoi(lastUserId) + 1 > 999){
        throw std::invalid_argument("Достигнут максимальный лимит пользователей.");
    }
    userId = std::to_string(std::stoi(lastUserId) + 1);
    int zSize = 3 - userId.length();
    User newUser(name, "USR_" + std::string(zSize, '0') + userId);

    return newUser;
}
