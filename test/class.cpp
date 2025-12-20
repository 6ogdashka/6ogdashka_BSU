#include <iostream>
#include "Book.h"

class Library {

    public:
    Book* begin() {
        return Library_;
    }

    Book* end() {
        return (Library_+size);
    }

    Library() = default;

    private:
        Book* Library_; 
        size_t size;
};

int main () {
    Library lib;
    std::sort(lib.begin(),lib.end(),[](const Book& a,const Book& b) { return a.BookName_ < b.BookName_;});

}