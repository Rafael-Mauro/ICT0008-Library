#include <iostream>
#include <string>
#include "Book.h"

int main()
{
    const int bookCount = 5;
    Book books[bookCount];

    // Initialize five books for the library.
    books[0].setBookDetails(
        "The Hobbit",
        "J. R. R. Tolkien",
        "9780261103344",
        true,
        "2026-11-19"
    );

    books[1].setBookDetails(
        "1984",
        "George Orwell",
        "9780451524935",
        false,
        "2026-11-19"
    );

    books[2].setBookDetails(
        "Pride and Prejudice",
        "Jane Austen",
        "9780141439518",
        true,
        "2026-11-19"
    );

    books[3].setBookDetails(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        true,
        "2026-11-19"
    );

    books[4].setBookDetails(
        "The Pragmatic Programmer",
        "David Thomas and Andrew Hunt",
        "9780135957059",
        true,
        "2026-11-19"
    );

    std::cout << "Library Management System\n";
    std::cout << "Books in the library:\n";

    // Display all five books.
    for (int i = 0; i < bookCount; ++i)
    {
        books[i].displayBookDetails();
    }

    // Keep accepting requests until the user enters 0.
    while (true)
    {
        std::string requestedISBN;

        std::cout << "\nEnter the ISBN of the book to borrow";
        std::cout << " (or 0 to exit): ";

        if (!std::getline(std::cin, requestedISBN))
        {
            std::cout << "\nInput ended. Closing the program.\n";
            break;
        }

        if (requestedISBN == "0")
        {
            std::cout << "Thank you. Goodbye!\n";
            break;
        }

        bool found = false;

        // Search the array for a matching ISBN.
        for (int i = 0; i < bookCount; ++i)
        {
            if (books[i].getISBN() == requestedISBN)
            {
                found = true;

                if (books[i].borrowBook())
                {
                    std::cout << "Book borrowed successfully.\n";
                }
                else
                {
                    std::cout
                        << "Error: This book is already borrowed.\n";
                }

                books[i].displayBookDetails();
                break;
            }
        }

        if (!found)
        {
            std::cout << "Error: No book found with that ISBN.\n";
        }
    }

    return 0;
}
