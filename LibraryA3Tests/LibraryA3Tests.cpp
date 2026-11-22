#include <iostream>
#include "Book.h"
#include <stdexcept>

int main()
{
    std::cout << "Library A3 - Test Application\n";
    std::cout << "Test 1: Valid book initialisation\n";

    Book book;

    book.setBookDetails(
        "The Hobbit",
        "J. R. R. Tolkien",
        "9780261103344",
        true,
        "2026-11-19"
    );

    book.displayBookDetails();

    std::cout << "\nTest 2: Valid Twilight initialisation\n";

    Book book2;

    book2.setBookDetails(
        "Twilight",
        "Stephenie Meyer",
        "9780316160179",
        false,
        "2026-11-19"
    );

    book2.displayBookDetails();

    std::cout << "\nTest 3: Valid The Lightning Thief initialisation\n";

    Book book3;

    book3.setBookDetails(
        "The Lightning Thief",
        "Rick Riordan",
        "9780786838653",
        true,
        "2026-11-19"
    );

    book3.displayBookDetails();

    std::cout << "\nTest 4: Invalid initialisation - empty title\n";

    try
    {
        Book invalidBook;

        invalidBook.setBookDetails(
            "",
            "J. R. R. Tolkien",
            "9780261103344",
            true,
            "2026-11-19"
        );

        std::cout << "TEST FAILED: Empty title was accepted.\n";
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "TEST PASSED: " << error.what() << "\n";
    }

    std::cout << "\nTest 5: Invalid initialisation - short ISBN\n";

    try
    {
        Book invalidBook2;

        invalidBook2.setBookDetails(
            "Twilight",
            "Stephenie Meyer",
            "123",
            false,
            "2026-11-19"
        );

        std::cout << "TEST FAILED: Short ISBN was accepted.\n";
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "TEST PASSED: " << error.what() << "\n";
    }

    std::cout << "\nTest 6: Invalid initialisation - impossible date\n";

    try
    {
        Book invalidBook3;

        invalidBook3.setBookDetails(
            "The Lightning Thief",
            "Rick Riordan",
            "9780786838653",
            true,
            "2026-02-30"
        );

        std::cout << "TEST FAILED: Impossible date was accepted.\n";
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "TEST PASSED: " << error.what() << "\n";
    }

    std::cout << "\nTest 7: Sorting an ascending array\n";

    Book ascendingBooks[3] = { book, book2, book3 };

    std::cout << "Before sorting:\n";

    for (int i = 0; i < 3; ++i)
    {
        std::cout << ascendingBooks[i].getISBN() << "\n";
    }

    Book::sortBookData(ascendingBooks, 3);

    std::cout << "After sorting:\n";

    for (int i = 0; i < 3; ++i)
    {
        std::cout << ascendingBooks[i].getISBN() << "\n";
    }

    bool correctOrder =
        ascendingBooks[0].getISBN() == "9780261103344" &&
        ascendingBooks[1].getISBN() == "9780316160179" &&
        ascendingBooks[2].getISBN() == "9780786838653";

    if (correctOrder)
    {
        std::cout << "TEST PASSED: Correct ascending ISBN order.\n";
    }
    else
    {
        std::cout << "TEST FAILED: Unexpected ISBN order.\n";
    }

    std::cout << "\nTest 8: Sorting a descending array\n";

    Book descendingBooks[3] = { book3, book2, book };

    std::cout << "Before sorting:\n";

    for (int i = 0; i < 3; ++i)
    {
        std::cout << descendingBooks[i].getISBN() << "\n";
    }

    Book::sortBookData(descendingBooks, 3);

    std::cout << "After sorting:\n";

    for (int i = 0; i < 3; ++i)
    {
        std::cout << descendingBooks[i].getISBN() << "\n";
    }

    bool correctDescendingOrder =
        descendingBooks[0].getISBN() == "9780261103344" &&
        descendingBooks[1].getISBN() == "9780316160179" &&
        descendingBooks[2].getISBN() == "9780786838653";

    if (correctDescendingOrder)
    {
        std::cout << "TEST PASSED: Descending input sorted correctly.\n";
    }
    else
    {
        std::cout << "TEST FAILED: Unexpected ISBN order.\n";
    }

    std::cout << "\nTest 9: Sorting a mixed-order array\n";

    Book mixedBooks[3] = { book2, book, book3 };

    std::cout << "Before sorting:\n";

    for (int i = 0; i < 3; ++i)
    {
        std::cout << mixedBooks[i].getISBN() << "\n";
    }

    Book::sortBookData(mixedBooks, 3);

    std::cout << "After sorting:\n";

    for (int i = 0; i < 3; ++i)
    {
        std::cout << mixedBooks[i].getISBN() << "\n";
    }

    bool correctMixedOrder =
        mixedBooks[0].getISBN() == "9780261103344" &&
        mixedBooks[1].getISBN() == "9780316160179" &&
        mixedBooks[2].getISBN() == "9780786838653";

    if (correctMixedOrder)
    {
        std::cout << "TEST PASSED: Mixed input sorted correctly.\n";
    }
    else
    {
        std::cout << "TEST FAILED: Unexpected ISBN order.\n";
    }

    return 0;
}
