#include <iostream>
#include <string>
#include "Book.h"
#include <stdexcept>

int main()
{
    // Temporary validation test: an impossible date must be rejected.
    std::cout << "Validation test: invalid date\n";

    try
    {
        Book invalidBook;

        invalidBook.setBookDetails(
            "The Lightning Thief",
            "Rick Riordan",
            "9780786838653",
            true,
            "2026-02-30"
        );

        std::cout << "TEST FAILED: Invalid data was accepted.\n";
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "TEST PASSED: " << error.what() << "\n";
    }

    std::cout << "\n";

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
        "Twilight",
        "Stephenie Meyer",
        "9780316160179",
        false,
        "2026-11-19"
    );

    books[2].setBookDetails(
        "The Lightning Thief",
        "Rick Riordan",
        "9780786838653",
        true,
        "2026-11-19"
    );

    books[3].setBookDetails(
        "Harry Potter and the Philosopher's Stone",
        "J. K. Rowling",
        "9781408855652",
        true,
        "2026-11-19"
    );

    books[4].setBookDetails(
        "The Hunger Games",
        "Suzanne Collins",
        "9780439023481",
        true,
        "2026-11-19"
    );

    // Sort the books before displaying the catalogue.
    Book::sortBookData(books, bookCount);

    std::cout << "Library Management System\n";
    std::cout << "Books in the library (sorted by ISBN):\n";

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
