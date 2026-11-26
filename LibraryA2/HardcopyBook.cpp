#include "HardcopyBook.h"
#include <iostream>
#include <stdexcept>

void HardcopyBook::setShelfNumber(const std::string& value)
{
    if (value.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument(
            "Shelf number cannot be empty."
        );
    }

    shelfNumber = value;
}

void HardcopyBook::displayBookDetails() const
{
    Book::displayBookDetails();

    std::cout << "Shelf number: " << shelfNumber << "\n";
}