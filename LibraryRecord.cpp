//Tsering Gurung
//3/24/23
//LibraryRecord.cpp
//Project 4: Polymorphism
#include "LibraryRecord.hpp"
#include "Textbook.hpp"
#include "Manual.hpp"
#include "Novel.hpp"

/** default constructor**/
LibraryRecord::LibraryRecord() : ArrayBag<Book*>() {}

/**
 * @param:  A refrence to a file name (string)
 * @post:   will read the input file, where each line corresponds to a Book subclass and dynamically allocate Book-derived
 *          objects with the information read from the input file and add them to the LibraryRecord.
 * @note:   Input data will be in the following format:
 *          title, author, page_count, is_digital, genre, subject, grade_level, has_film_adaptation, has_review_questions, device_model, website, book_type
*/
LibraryRecord::LibraryRecord(const std::string& input_file) {
    item_count_ = 0;
    std::string scrap, input_title, input_author, input_page_count, input_is_digital, input_genre, input_subject, input_grade_level, input_has_film, input_has_review_questions, input_device_model, input_website, input_book_type;

    std::ifstream data_file(input_file);
    if(!data_file.is_open()) {
        std::cout << "ERROR OPENING FILE" << '\n';
        return;
    }

    std::getline(data_file, scrap, '\n');

    while(data_file.good()){
        std::getline(data_file, input_title, ',');
        std::getline(data_file, input_author, ',');
        std::getline(data_file, input_page_count, ',');
        std::getline(data_file, input_is_digital, ',');
        std::getline(data_file, input_genre, ',');
        std::getline(data_file, input_subject, ',');
        std::getline(data_file, input_grade_level, ',');
        std::getline(data_file, input_has_film, ',');
        std::getline(data_file, input_has_review_questions, ',');
        std::getline(data_file, input_device_model, ',');
        std::getline(data_file, input_website, ',');
        std::getline(data_file, input_book_type, '\n');
        
        if (input_book_type == "1") {
            Novel* new_novel = new Novel(input_title, input_author, std::stoi(input_page_count), input_genre, std::stoi(input_is_digital), std::stoi(input_has_film));
            add(new_novel);
        }
        if(input_book_type == "2"){
            Textbook* new_textbook = new Textbook(input_title, input_author, std::stoi(input_page_count), input_subject, std::stoi(input_is_digital), stringToGradeLevel(input_grade_level), std::stoi(input_has_review_questions));
            add(new_textbook);
        }
        if(input_book_type == "3"){
            Manual* new_manual = new Manual(input_title, input_author, std::stoi(input_page_count), input_device_model, std::stoi(input_is_digital), input_website);
            add(new_manual);
        }
    }
}

/** 
 * @param:   A reference to a Book object to be checked in
 * @return:  returns true if a book was successfully added to items_, false otherwise
 * @post:    adds book to items_.
 **/
bool LibraryRecord::checkIn(Book* new_book) {
    return add(new_book);
}

/** 
 * @param:   A reference to a Book object to be checked out   
 * @return:  returns true if a book was successfully removed from items_, false otherwise
 * @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the vector of checked-out books.
 */
bool LibraryRecord::checkOut(Book* a_book) {
    if(remove(a_book)) {
        checked_out_books_.push_back(a_book);
        return true;
    }
    return false;
}

/**
 * @param:   A reference to a Book object
 * @return:  The number of times (int) the referenced Book has been checked out
 */
int LibraryRecord::getCheckOutHistory(Book* a_book) const {
    int check_out_counter = 0;
    for(int i = 0; i < checked_out_books_.size(); i++)
        if(checked_out_books_[i] == a_book)
            check_out_counter++;
    return check_out_counter;
}

/**
 * @post:   Outputs the names of the Books in the LibraryRecord and the number of times each Book has been cheked out
 *          For each Book in the LibraryRecord you will output:
 *          "[title_] is written by [author_]. Page Count: [page_count_]. [It is / It is not] available digitally.\n
 *          It has been checked out [_] times.\n"
 */
void LibraryRecord::display() const {
    for(int i = 0; i < item_count_; i++){
        items_[i]->display();
        std::cout << "It has been checked out " << getCheckOutHistory(items_[i]) << " times.\n";    
    }
}

/**
 * @post:    Prints the title of each Book in the LibraryRecord
 * Example: "title1, title2, title3, title4!\n" Note the commas and exclamation mark.
 */
void LibraryRecord::displayTitles() const {
    for(int i = 0; i < item_count_; i++) {
        std::cout << items_[i]->getTitle();
        if(i < item_count_ - 1) 
            std::cout << ", ";
        else   
            std::cout << "!";
    }
    std::cout << "\n";
}

/**
 * @param:  refrence to a key (string)
 * @post:   displays information of its holdings whenever they key matches the relevant 
 *          information (specific to the type of book).
*/
void LibraryRecord::displayFilter(const std::string& key) {
    for(int i = 0; i < item_count_; i++) 
        items_[i]->displayFilter(key);
}

/**
 * @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
 * @post:      Duplicates all the items in the LibraryRecord
 * Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
bool LibraryRecord::duplicateStock() {
    if(item_count_ == 0) return false;
    if(item_count_ * 2 > DEFAULT_CAPACITY) return false;

    int currentItemCount = item_count_;
    for(int i = 0; i < currentItemCount; i++)
        add(items_[i]);

    return true;
}

/**
 * @param:   A reference to a book
 * @return: True if at least one copy of the referenced book was removed from items_, false otherwise 
 * @post: remove all occurrences of the referenced book
*/
bool LibraryRecord::removeStock(Book* a_book) {
    while(remove(a_book));
    return true;
}

/**
 * @param:   A reference to another LibraryRecord
 * @return:  Returns true if the 2 library records have the same contents (including the same number of duplicates for each book), regardless of their order. For example, 
 *           if the current holdings of the LibraryRecord are [book1, book2, book3]
 *           and those of the referenced LibraryRecord are [book3, book1, book2], it will return true.
 *           However, [book1, book2, book2, book3] is not equivalent to [book1, book2, book3, book3], because it contains two copies of book2 and only one copy of book3
 */
bool LibraryRecord::equivalentRecords(const LibraryRecord& new_library) const {
    if(item_count_ != new_library.item_count_) return false;
    for(Book* book : items_)
        if(getFrequencyOf(book) != new_library.getFrequencyOf(book)) return false;
    return true;
}

/**
 * @param:   A reference to another LibraryRecord object
 * @post:    Combines the contents from both LibraryRecord objects, including duplicates.
 * Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]
 * IMPORTANT: We are carrying over the number of times a book has been checked out. For example, if we have LibraryRecord1 += LibraryRecord2 and
 * book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the += operation
 * Hint: use getCheckOutHistory and the checkout history vector
 */
LibraryRecord& LibraryRecord::operator+= (const LibraryRecord& new_library) {
    for(int i = 0; i < new_library.item_count_; i++)
        add(new_library.items_[i]);
    checked_out_books_.insert(checked_out_books_.end(), new_library.checked_out_books_.begin(), new_library.checked_out_books_.end());
    return *this;
}

/**
 * @param:   A reference to another LibraryRecord object
 * @post:    Combines the contents from both LibraryRecord objects, EXCLUDING duplicates.
 * Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]
 * IMPORTANT: We are carrying over the nunber of times a book has been checked out. For example, if we have LibraryRecord1 /= LibraryRecord2 and
 * book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the /= operation
 * Hint: use getCheckOutHistory and the checkout history vector
*/
LibraryRecord& LibraryRecord::operator/= (const LibraryRecord& new_library) {
    for(int i = 0; i < new_library.item_count_; i++)
        if(!contains(new_library.items_[i]))
            add(new_library.items_[i]);
    checked_out_books_.insert(checked_out_books_.end(), new_library.checked_out_books_.begin(), new_library.checked_out_books_.end());
    return *this;
}        
