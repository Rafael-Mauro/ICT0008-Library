#include "Book.h"
#include <iostream>

// Assign the supplied information to this book.
void Book::setBookDetails(
    const std::string& bookTitle,
    const std::string& bookAuthor,
    const std::string& bookISBN,
    bool bookAvailability,
    const std::string& bookDateAdd
)
{
    title = bookTitle;
    author = bookAuthor;
    isbn = bookISBN;
    availability = bookAvailability;
    dateAdd = bookDateAdd;
}

// Display the current book information.
void Book::displayBookDetails() const
{
    std::cout << "\n--- Book Details ---\n";
    std::cout << "Title: " << title << "\n";
    std::cout << "Author: " << author << "\n";
    std::cout << "ISBN: " << isbn << "\n";

    if (availability)
    {
        std::cout << "Availability: Available\n";
    }
    else
    {
        std::cout << "Availability: Borrowed\n";
    }

    std::cout << "Date added: " << dateAdd << "\n";
}

// Borrow the book only if it is available.
bool Book::borrowBook()
{
    if (!availability)
    {
        return false;
    }

    availability = false;
    return true;
}

// Mark the book as available again.
void Book::returnBook()
{
    availability = true;
}
