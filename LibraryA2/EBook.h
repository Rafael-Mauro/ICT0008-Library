#pragma once

#include <string>
#include "Book.h"

class EBook : public Book
{
private:
    std::string endOfLicenseDate;

public:
    void setEndOfLicenseDate(const std::string& value);

    void displayBookDetails() const override;

    bool borrowBook() override;
};