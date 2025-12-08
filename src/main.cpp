#include <iostream>
#include "User.cpp"
#include "Book.cpp"
#include "Library.cpp"

int main() {
    Library library("../data/library_data.txt");

    User user1("Алексей", "USR_001");
    user1.addBook("9781");
    user1.addBook("9782");
    user1.displayProfile();

    return 0;
}