//Tsering Gurung
//CS 235
//Project 4: Polymorphism
#include "Textbook.hpp"

/**
 * Parameterized constructor.
 * @param     : The title of the book (a string)
 * @param     : The author of the book (a string)
 * @param     : The number of pages in the book (a positive integer)
 * @param     : The subject of the book (a string)
 * @param     : A flag indicating whether the book is in digital form
 *              with DEFAULT VALUE False (a Boolean)
 * @param     : The grade level of the book (of type grade_level)
 *              with DEFAULT VALUE NONE
 * @param     : A boolean to indicate whether the book has review
 *              questions with DEFAULT VALUE False
 * @post      : The private members are set to the values of the
 *              corresponding parameters.
*/
Textbook::Textbook(std::string title, std::string author, int page_count, std::string subject, bool is_digital, grade_level level, bool has_review_questions) : 
    Book(title, author, page_count, is_digital),
    subject_(subject),
    level_(level),
    has_review_questions_(has_review_questions) {   }

/**
 * @param  : a reference to a string representing the the subject of the book
 * @post   : sets the private member variable to the value of the parameter
*/
void Textbook::setSubject(const std::string& subject) {
    subject_ = subject;
}

/**
 * @return  : the subject of the textbook
*/
std::string Textbook::getSubject() const {
    return subject_;
}

/**
 * @param  : a reference to a grade_level
 * @post   : sets the private member variable to the value of the parameter
*/
void Textbook::setGradeLevel(const grade_level& level) {
    level_ = level;
}

/**
 * @return  : a string representative of the grade_level
 *              (e.g. if the grade level is JUNIOR_HIGH,
 *              it returns "JUNIOR HIGH")
*/
std::string Textbook::getGradeLevel() const {
    if(level_ == NONE)        return "NONE";
    if(level_ == ELEMENTARY)  return "ELEMENTARY";
    if(level_ == JUNIOR_HIGH) return "JUNIOR HIGH";
    if(level_ == HIGH_SCHOOL) return "HIGH SCHOOL";
    if(level_ == COLLEGE)     return "COLLEGE";
    
    return "If you get here, we got a problem";
}

/**
 * @post   : sets the review question flag to True
*/
void Textbook::setReviewQuestions() {
    has_review_questions_ = true;
}

/**
 * @return  : the flag indicating if the texbook has review questions
*/
bool Textbook::checkReviewQuestions() const {
    return has_review_questions_;
}

/**
 * @post     : displays Textbook data in the form:
 * "[title_] is written by [author_] for [grade_level] students. Subject: [subject]. [It has/ It does not have] review questions. Page Count: [page_count_]. [It is / It is not] available digitally.\n" 
*/ 
void Textbook::display() const {
    std::cout << getTitle() << " is written by " << getAuthor() << " for " << getGradeLevel() << " students. Subject: " << getSubject() << ". " << (checkReviewQuestions() ? "It has" : "It does not have") << " review questions. " << "Page Count: " << getPageCount() << ". " << (isDigital() ? "It is" : "It is not") << " available digitally.\n";
}

/**
 * @param    : a reference to a string key to match the subject of the Textbook
 * @post     : calls display() if the key argument is equal to subject_ (e.g. "mathematics")   
*/
void Textbook::displayFilter(const std::string& key) const {
    if(key == subject_) display();
}

/**
 * @param   : refrence to (string) grade_level.
 * @return  : returns (enum) grade_level.
*/
grade_level stringToGradeLevel(const std::string& input) {
    if(input == "ELEMENTARY")   return ELEMENTARY;
    if(input == "JUNIOR_HIGH")  return JUNIOR_HIGH;
    if(input == "HIGH_SCHOOL")  return HIGH_SCHOOL;
    if(input == "COLLEGE")      return COLLEGE;
    return NONE;
}
