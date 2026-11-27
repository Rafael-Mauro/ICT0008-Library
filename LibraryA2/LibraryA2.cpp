#include <iostream>
#include <string>
#include "Book.h"
#include "HardcopyBook.h"
#include "EBook.h"

int main()
{
    const int bookCount = 5;

    // Three physical books with shelf locations.
    HardcopyBook hobbit;
    hobbit.setBookDetails(
        "The Hobbit",
        "J. R. R. Tolkien",
        "9780261103344",
        true,
        "2026-11-19"
    );
    hobbit.setShelfNumber("A2-03");

    HardcopyBook twilight;
    twilight.setBookDetails(
        "Twilight",
        "Stephenie Meyer",
        "9780316160179",
        false,
        "2026-11-19"
    );
    twilight.setShelfNumber("B1-02");

    HardcopyBook harryPotter;
    harryPotter.setBookDetails(
        "Harry Potter and the Philosopher's Stone",
        "J. K. Rowling",
        "9781408855652",
        true,
        "2026-11-19"
    );
    harryPotter.setShelfNumber("A3-01");

    // Two ebooks with demonstration license dates.
    // This license is already expired.
    EBook lightningThief;
    lightningThief.setBookDetails(
        "The Lightning Thief",
        "Rick Riordan",
        "9780786838653",
        true,
        "2026-11-19"
    );
    lightningThief.setEndOfLicenseDate("2026-11-20");

    // A future license permits borrowing while the book is available.
    EBook hungerGames;
    hungerGames.setBookDetails(
        "The Hunger Games",
        "Suzanne Collins",
        "9780439023481",
        true,
        "2026-11-19"
    );
    hungerGames.setEndOfLicenseDate("2099-12-31");

    // The objects above remain alive throughout main().
    // Non-owning pointers keep the complete derived objects intact.
    Book* books[bookCount] = {
        &hobbit,
        &twilight,
        &lightningThief,
        &harryPotter,
        &hungerGames
    };

    // Select the pointer overload of Insertion Sort.
    Book::sortBookData(books, bookCount);

    std::cout << "Library Management System - Phase 2\n";
    std::cout << "Books in the library (sorted by ISBN):\n";

    for (int i = 0; i < bookCount; ++i)
    {
        // Virtual dispatch also displays the shelf or license information.
        books[i]->displayBookDetails();
    }

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

        for (int i = 0; i < bookCount; ++i)
        {
            if (books[i]->getISBN() == requestedISBN)
            {
                found = true;

                // EBook checks its license before the base availability check.
                if (books[i]->borrowBook())
                {
                    std::cout << "Book borrowed successfully.\n";
                }
                else
                {
                    // A false result may mean a loan or a license restriction.
                    std::cout << "Error: Borrowing denied. The book is already"
                        << " borrowed or its ebook license is not valid.\n";
                }

                books[i]->displayBookDetails();
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
