#include "Book.h"
#include <iostream>
#include <stdexcept>

// Validate the information before updating the book.
void Book::setBookDetails(
    const std::string& bookTitle,
    const std::string& bookAuthor,
    const std::string& bookISBN,
    bool bookAvailability,
    const std::string& bookDateAdd
)
{
    if (bookTitle.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument("Title cannot be empty.");
    }

    if (bookAuthor.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument("Author cannot be empty.");
    }

    if (bookISBN.size() != 13)
    {
        throw std::invalid_argument(
            "ISBN must contain exactly 13 digits."
        );
    }

    int checksum = 0;

    for (int i = 0; i < 13; ++i)
    {
        if (bookISBN[i] < '0' || bookISBN[i] > '9')
        {
            throw std::invalid_argument(
                "ISBN must contain digits only."
            );
        }

        int digit = bookISBN[i] - '0';
        int weight = (i % 2 == 0) ? 1 : 3;

        checksum += digit * weight;
    }

    if (bookISBN.substr(0, 3) != "978" &&
        bookISBN.substr(0, 3) != "979")
    {
        throw std::invalid_argument(
            "ISBN must start with 978 or 979."
        );
    }

    if (checksum % 10 != 0)
    {
        throw std::invalid_argument(
            "ISBN check digit is invalid."
        );
    }

    // Validate the date format.
    if (bookDateAdd.size() != 10 ||
        bookDateAdd[4] != '-' ||
        bookDateAdd[7] != '-')
    {
        throw std::invalid_argument(
            "Date must use the format YYYY-MM-DD."
        );
    }

    // All characters except the separators must be digits.
    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
        {
            continue;
        }

        if (bookDateAdd[i] < '0' || bookDateAdd[i] > '9')
        {
            throw std::invalid_argument(
                "Date must use the format YYYY-MM-DD."
            );
        }
    }

    // Extract the year, month and day.
    int year = std::stoi(bookDateAdd.substr(0, 4));
    int month = std::stoi(bookDateAdd.substr(5, 2));
    int day = std::stoi(bookDateAdd.substr(8, 2));

    if (year < 1 || month < 1 || month > 12)
    {
        throw std::invalid_argument(
            "Date contains an invalid year or month."
        );
    }

    int daysInMonth[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    // February has 29 days in a leap year.
    bool leapYear =
        (year % 4 == 0 && year % 100 != 0) ||
        year % 400 == 0;

    if (leapYear)
    {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1])
    {
        throw std::invalid_argument(
            "Date contains an invalid day."
        );
    }

    // Update the attributes only after all checks pass.
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

// Return the ISBN without changing the book.
std::string Book::getISBN() const
{
    return isbn;
}

// Sort complete Book objects by ISBN in ascending order.
void Book::sortBookData(Book books[], int count)
{
    for (int i = 1; i < count; ++i)
    {
        Book key = books[i];
        int j = i - 1;

        // Move books with larger ISBNs one position to the right.
        while (j >= 0 && books[j].getISBN() > key.getISBN())
        {
            books[j + 1] = books[j];
            --j;
        }

        // Insert the selected book in its correct position.
        books[j + 1] = key;
    }
}

// Sort pointers to complete books, preserving derived-class data.
void Book::sortBookData(Book* books[], int count)
{
    for (int i = 1; i < count; ++i)
    {
        Book* key = books[i];
        int j = i - 1;

        // Move pointers whose books have larger ISBNs.
        while (j >= 0 &&
            books[j]->getISBN() > key->getISBN())
        {
            books[j + 1] = books[j];
            --j;
        }

        // Insert the pointer in its correct position.
        books[j + 1] = key;
    }
}
