#pragma once

#include <string>
#include "Book.h"

class HardcopyBook : public Book
{
private:
    std::string shelfNumber;

public:
    void setShelfNumber(const std::string& value);

    void displayBookDetails() const override;
};
