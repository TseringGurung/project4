#include "Book.hpp"

Book::Book(const std::string& title, const std::string& author, const int& page_count, const bool& is_digital) : 
    title_(title), 
    author_(author), 
    page_count_(page_count), 
    is_digital_(is_digital) {   }

bool Book::operator== (Book const &book_two) const {
    if(title_ != book_two.title_)   return false;
    if(author_ != book_two.author_) return false;
    if(page_count_ != book_two.page_count_) return false;
    if(is_digital_ != book_two.is_digital_) return false;
    return true;
}

bool Book::operator!= (Book const &book_two) const {
    if(title_ != book_two.title_)   return true;
    if(author_ != book_two.author_) return true;
    if(page_count_ != book_two.page_count_) return true;
    if(is_digital_ != book_two.is_digital_) return true;
    return false;     
}

void Book::setTitle(const std::string& title) {   title_ = title;   }

void Book::setAuthor(const std::string& author) {   author_ = author;   }

void Book::setPageCount(const int& page_count) {   page_count_ = page_count > 0 ? page_count : page_count_ ;   }

void Book::setDigital() {   is_digital_ = true;   }

std::string Book::getTitle() const {   return title_;   }

std::string Book::getAuthor() const {   return author_;   }

int Book::getPageCount() const {   return page_count_;   }

bool Book::isDigital() const {   return is_digital_;   }
