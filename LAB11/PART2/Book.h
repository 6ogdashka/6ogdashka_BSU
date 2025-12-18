#ifndef BOOK_H
#define BOOK_H

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <initializer_list>

struct Author {
    Author(const std::string& FirstName, const std::string& SecondName, const std::string& ThirdName)
        : FirstName_(FirstName), SecondName_(SecondName), ThirdName_(ThirdName) {}
    
    Author(const Author& a) = default;
    Author(Author&& a) = default;
    ~Author() = default;
    
    Author& operator=(const Author& a) = default;

    bool operator==(const Author& other) const {
        return ((FirstName_ == other.FirstName_) && (SecondName_ == other.SecondName_) && (ThirdName_ == other.ThirdName_));
    }
    
    bool operator!=(const Author& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Author& other) const {
        if (SecondName_ != other.SecondName_) return SecondName_ < other.SecondName_;
        if (FirstName_ != other.FirstName_) return FirstName_ < other.FirstName_;
        return ThirdName_ < other.ThirdName_;
    }
    
    std::string FirstName_{};
    std::string SecondName_{};
    std::string ThirdName_{};

    friend std::ostream& operator<<(std::ostream& out, const Author& Author) {
        out << Author.FirstName_ << " " << Author.SecondName_ << " " << Author.ThirdName_;
        return out;
    }
};

struct Data {
    Data() = default;
    
    Data(size_t Year) : Year_(Year) {}
    
    ~Data() = default;
    
    Data& operator=(const Data& a) = default;
    
    size_t Year_{};

    friend std::ostream& operator<<(std::ostream& out, const Data& Data) {
        out << Data.Year_;
        return out;
    }
};

struct Book {
    Book(size_t UDK, const std::string& BookName, 
         std::list<Author> Authors, const Data& Data)
        : UDK_(UDK), BookName_(BookName), Authors_(Authors), Data_(Data) {
            Authors_.sort([](const Author& a, const Author& b) {return a.SecondName_ < b.SecondName_;});
        }
    
    Book(size_t UDK, const std::string& BookName, const Data& Data)
        : UDK_(UDK), BookName_(BookName), Data_(Data) {}
    
    size_t UDK_{};
    std::string BookName_;
    std::list<Author> Authors_; 
    Data Data_{};
    
    bool Equal(const std::string& Name) const {
        return (Name == BookName_); 
    }

    bool operator==(const Book& other) const {
        return (UDK_ == other.UDK_) && (BookName_ == other.BookName_);
    }

    bool operator!=(const Book& other) const {
        return !(*this == other);
    }

    bool operator<(const Book& other) const {
        if (BookName_ != other.BookName_) {
            return BookName_ < other.BookName_;
        }
        return UDK_ < other.UDK_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Book& Book) {
        out << "Название: " << Book.BookName_ << '\n'
              << "УДК: " << Book.UDK_ << '\n'
              << "Авторы: ";
        
        if (!Book.Authors_.empty()) {
            auto it = Book.Authors_.begin();
            out << *it;
            ++it;
            
            for (; it != Book.Authors_.end(); ++it) {
                out << ", " << *it;
            }
        } else {
            out << "Нет авторов";
        }
        
        out << '\n'
              << "Дата издания: " << Book.Data_ << '\n';
        
        return out;
    }
};

#endif