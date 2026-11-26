#include "EBook.h"
#include <ctime>
#include <iostream>
#include <stdexcept>

void EBook::setEndOfLicenseDate(const std::string& value)
{
    // Check the YYYY-MM-DD format before extracting numbers.
    if (value.size() != 10 || value[4] != '-' || value[7] != '-')
    {
        throw std::invalid_argument(
            "License date must use the format YYYY-MM-DD."
        );
    }

    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
        {
            continue;
        }

        if (value[i] < '0' || value[i] > '9')
        {
            throw std::invalid_argument(
                "License date must use the format YYYY-MM-DD."
            );
        }
    }

    int year = std::stoi(value.substr(0, 4));
    int month = std::stoi(value.substr(5, 2));
    int day = std::stoi(value.substr(8, 2));

    if (year < 1 || month < 1 || month > 12)
    {
        throw std::invalid_argument(
            "License date contains an invalid year or month."
        );
    }

    int daysInMonth[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool leapYear =
        (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (leapYear)
    {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1])
    {
        throw std::invalid_argument(
            "License date contains an invalid day."
        );
    }

    // Preserve the previous value if validation fails.
    endOfLicenseDate = value;
}

void EBook::displayBookDetails() const
{
    Book::displayBookDetails();

    std::cout << "End of license date: " << endOfLicenseDate << "\n";
}

bool EBook::borrowBook()
{
    // No loan is allowed until a valid license date has been set.
    if (endOfLicenseDate.empty())
    {
        return false;
    }

    std::time_t now = std::time(nullptr);

    if (now == static_cast<std::time_t>(-1))
    {
        return false;
    }

    std::tm localDate{};

#ifdef _MSC_VER
    // Microsoft Visual Studio uses the secure localtime_s function.
    if (localtime_s(&localDate, &now) != 0)
    {
        return false;
    }
#else
    // Portable fallback for other compilers, such as GCC.
    const std::tm* result = std::localtime(&now);

    if (result == nullptr)
    {
        return false;
    }

    localDate = *result;
#endif

    char today[11];

    if (std::strftime(today, sizeof(today), "%Y-%m-%d", &localDate) != 10)
    {
        return false;
    }

    // Valid YYYY-MM-DD strings can be compared chronologically.
    // The license remains valid through its end date (inclusive).
    if (endOfLicenseDate < std::string(today))
    {
        return false;
    }

    // The base class also checks whether the book is already borrowed.
    return Book::borrowBook();
}
