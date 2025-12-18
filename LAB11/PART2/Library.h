#ifndef LIBRARY_H
#define LIBRARY_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <set>
#include <map>
#include <list>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "Book.h"

class Library {
    public:
        Library() = default;
        ~Library() = default;

        Library& Add(const Book& book);
        Library& Delete(const Book& book);
        
        std::multiset<Book>::iterator FindBookByName(const std::string& name);
        std::list<Book> FindBooksByAuthor(const Author& author);
        
        template<typename Iterator>
        Iterator FindBookByName(Iterator begin, Iterator end, const std::string& Name) {
            for (auto it = begin; it != end; ++it) {
                if ((*it).BookName_ == Name) {
                    return it;
                }
            }
            return end;
        }
        
        template<typename Iterator>
        std::list<Book> FindBooksByAuthor(Iterator begin, Iterator end, const Author& Author) {
            std::list<Book> BooksWithAuthor{};
            for (auto it = begin; it != end; ++it) {
                if (std::find(it->Authors_.begin(), it->Authors_.end(), Author) != it->Authors_.end()) {
                    BooksWithAuthor.push_back(*it);
                }
            }
            return BooksWithAuthor;
        }
        
        Library& EraseAuthorInBook(const Book& book, const Author& author);
        Library& AddAuthorToBook(const Author& author, const Book& book);
        Library& EraseBookByName(const std::string& name);
        std::multiset<Book>::iterator begin();
        std::multiset<Book>::iterator end();
        std::multiset<Book>::const_iterator begin() const;
        std::multiset<Book>::const_iterator end() const;
        
        friend std::ostream& operator<<(std::ostream& out, const Library& library);

        size_t GetBookCount() const;
        size_t GetUniqueBookCount() const;

        void LoadFromFile(const std::string& filename);
        void SaveToFile(const std::string& filename) const;

    private:
        std::multiset<Book> Books_{};
};

#endif