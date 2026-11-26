#pragma once

#include <string>

class Book
{
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool availability = true;
    std::string dateAdd;

public:
    virtual ~Book() = default;
    void setBookDetails(
        const std::string& bookTitle,
        const std::string& bookAuthor,
        const std::string& bookISBN,
        bool bookAvailability,
        const std::string& bookDateAdd
    );

    virtual void displayBookDetails() const;

    virtual bool borrowBook();

    void returnBook();

    std::string getISBN() const;

    static void sortBookData(Book books[], int count);

};

