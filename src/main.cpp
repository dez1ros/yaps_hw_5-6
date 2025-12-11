#include <iostream>
#include "User.cpp"
#include "Book.cpp"
#include "Library.cpp"

int main() {
    Library library("library_data.txt");

    while (1) {
        int choice = mainMenu();

        if (choice == 1){
            library.displayAllBooks();
        } else if (choice == 2){
            library.displayAllUsers();
        } else if (choice == 3){
            
        }

        if (choice == 10) {
            library.saveToFile();
            std::cout << "Данные сохранены. Выход из программы.\n";
            break;
        }
    }   

    library.displayAllBooks();
    library.displayAllUsers();
    // User user1("Алексей", "USR_001");
    // user1.addBook("9781");
    // user1.addBook("9782");
    // user1.displayProfile();

    // Book book1("C++ Programming", "John Doe", 1500, "9781");
    // library.addBook(book1);
    
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
}