#include <iostream>
#include "Book.h"

int main()
{
    std::cout << "Library Management System\n";

    Book firstBook;

    firstBook.setBookDetails(
        "The Hobbit",
        "J. R. R. Tolkien",
        "9780261103344",
        true,
        "2026-11-19"
    );

    // Show the book before borrowing.
    firstBook.displayBookDetails();

    // First borrowing attempt: should succeed.
    std::cout << "\nAttempting to borrow the book...\n";

    if (firstBook.borrowBook())
    {
        std::cout << "Book borrowed successfully.\n";
    }
    else
    {
        std::cout << "Error: This book is already borrowed.\n";
    }

    firstBook.displayBookDetails();

    // Second borrowing attempt: should fail.
    std::cout << "\nAttempting to borrow the same book again...\n";

    if (firstBook.borrowBook())
    {
        std::cout << "Book borrowed successfully.\n";
    }
    else
    {
        std::cout << "Error: This book is already borrowed.\n";
    }

    // Return the book and show the updated status.
    std::cout << "\nReturning the book...\n";

    firstBook.returnBook();
    firstBook.displayBookDetails();

    return 0;
}
