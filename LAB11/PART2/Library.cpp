#include "Library.h"

class LibraryFileException : public std::runtime_error {
public:
    LibraryFileException(const std::string& message, size_t line = 0) 
        : std::runtime_error(message + (line ? " (строка: " + std::to_string(line) + ")" : "")) {}
};

class LibraryParseException : public LibraryFileException {
public:
    LibraryParseException(const std::string& message, size_t line = 0) 
        : LibraryFileException("Ошибка парсинга: " + message, line) {}
};

class LibraryFormatException : public LibraryFileException {
public:
    LibraryFormatException(const std::string& message, size_t line = 0) 
        : LibraryFileException("Неверный формат: " + message, line) {}
};

Library& Library::Add(const Book& book) {
    Books_.insert(book);
    return *this;
}

Library& Library::Delete(const Book& book) {
    auto it = Books_.find(book);
    if (it != Books_.end()) {
        Books_.erase(it);
    }
    return *this;
}

std::multiset<Book>::iterator Library::FindBookByName(const std::string& name) {
    return FindBookByName(Books_.begin(), Books_.end(), name);
}

std::list<Book> Library::FindBooksByAuthor(const Author& author) {
    return FindBooksByAuthor(Books_.begin(), Books_.end(), author);
}

Library& Library::EraseAuthorInBook(const Book& book, const Author& author) {
    auto range = Books_.equal_range(book);

    std::list<Book> modifiedBooks;
    
    for (auto it = range.first; it != range.second;) {
        Book modifiedBook = *it;
        
        modifiedBook.Authors_.remove(author);
        it = Books_.erase(it);
        Books_.insert(modifiedBook);
    }
    
    return *this;
}

Library& Library::AddAuthorToBook(const Author& author, const Book& book) {
    auto range = Books_.equal_range(book);
    
    for (auto it = range.first; it != range.second;) {
        Book modifiedBook = *it;
        
        auto authorIt = std::find(modifiedBook.Authors_.begin(), 
                                 modifiedBook.Authors_.end(), author);
        if (authorIt == modifiedBook.Authors_.end()) {
            modifiedBook.Authors_.push_back(author);
            modifiedBook.Authors_.sort([](const Author& a, const Author& b) {
                return a.SecondName_ < b.SecondName_;
            });
        }
        
        it = Books_.erase(it);
        
        Books_.insert(modifiedBook);
    }
    
    return *this;
}

Library& Library::EraseBookByName(const std::string& name) {
    auto it = FindBookByName(name);
    if (it != Books_.end()) {
        Books_.erase(it);
    }
    return *this;
}

std::multiset<Book>::iterator Library::begin() {
    return Books_.begin();
}

std::multiset<Book>::iterator Library::end() {
    return Books_.end();
}

std::multiset<Book>::const_iterator Library::begin() const {
    return Books_.begin();
}

std::multiset<Book>::const_iterator Library::end() const {
    return Books_.end();
}

std::ostream& operator<<(std::ostream& out, const Library& library) {
    for (const auto& book : library.Books_) {
        out << book << '\n';  
    }
    return out;
}

size_t Library::GetBookCount() const {
    return Books_.size(); 
}

size_t Library::GetUniqueBookCount() const {
    size_t uniqueCount = 0;
    std::set<Book> uniqueBooks;
    
    for (const auto& book : Books_) {
        uniqueBooks.insert(book);
    }
    
    return uniqueBooks.size();
}

void Library::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    Books_.clear();
    
    std::string line;
    size_t lineNum = 0;
    
    while (std::getline(file, line)) {
        lineNum++;
        
        if (line.empty()) continue;
        
        size_t udk = 0;
        try {
            if (!line.empty() && line.back() == '.') {
                line.pop_back();
            }
            udk = std::stoul(line);
        } catch (...) {
            throw LibraryParseException("Некорректный УДК", lineNum);
        }
        
        std::string bookName;
        if (!std::getline(file, bookName)) {
            throw LibraryFormatException("Неожиданный конец файла при чтении названия", lineNum);
        }
        lineNum++;
        
        if (!bookName.empty() && bookName.back() == '.') {
            bookName.pop_back();
        }
        
        std::string yearStr;
        if (!std::getline(file, yearStr)) {
            throw LibraryFormatException("Неожиданный конец файла при чтении года", lineNum);
        }
        lineNum++;
        
        size_t year = 0;
        try {
            if (!yearStr.empty() && yearStr.back() == '.') {
                yearStr.pop_back();
            }
            year = std::stoul(yearStr);
        } catch (...) {
            throw LibraryParseException("Некорректный год издания", lineNum);
        }
        
        Data data(year);
        std::list<Author> authors;
        
        while (std::getline(file, line)) {
            lineNum++;
            
            if (line.empty()) continue;
            
            if (line == ".") break;
            
            if (!line.empty() && line.back() == '.') {
                line.pop_back();
            }
            
            std::istringstream iss(line);
            std::string firstName, secondName, thirdName;
            if (iss >> firstName >> secondName >> thirdName) {
                authors.emplace_back(firstName, secondName, thirdName);
            } else {
                throw LibraryParseException("Некорректный формат автора", lineNum);
            }
        }
        
        Book book(udk, bookName, authors, data);
        Add(book);
    }
    
    file.close();
}

void Library::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    for (const auto& book : Books_) {

        file << book.UDK_ << ".\n";
        
        file << book.BookName_ << ".\n";
        
        file << book.Data_.Year_ << ".\n";

        for (const auto& author : book.Authors_) {
            file << author.FirstName_ << " " 
                 << author.SecondName_ << " " 
                 << author.ThirdName_ << ".\n";
        }
        
        file << ".\n";
    }
    
    file.close();
}