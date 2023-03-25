#ifndef BOOK_
#define BOOK_

#include <string>
#include <iostream>

class Book{

    private:
        std::string title_;     /* The title of the book (a string) */
        std::string author_;    /* The author of the book (a string) */
        int page_count_;        /* The page count (an integer) */
        bool is_digital_;       /* A flag indicating whether the book is available in digital form (a Boolean) */

    public:
        
        /**
         * Parameterized + Default constructor.
         * @param      : The title of the book (a string) default = ""
         * @param      : The author of the book (a string) default = ""
         * @param      : The number of pages in the book (a positive int) default = 0
         * @param      : A flag indicating whether the book is in digital form (a Boolean),
         *                 with default value False default = false
         * @post       : The private members are set to the values of the corresponding parameters.
        */
        Book(const std::string& title = "", const std::string& author = "", const int& page_count = 0, const bool& is_digital = false);
        
        /**
         * @param : A reference to the right hand side of the == operator.
         * @return : Returns true if the right hand side book is the identical, false otherwise.
         * Note: ALL attributes must be equal for two books to be deemed equal.
         * Example: In order for book1 to be == to book 2 we must have:
         * - The same title
         * - The same author
         * - The same page count
         * - They must either be both digital or both not
        */
        bool operator== (Book const &book_two) const;

        /**
         * @param : A reference to the right hand side of the != operator.
         * @return : Returns true if the right hand side book is NOT identical (!=), false otherwise.
         * Note: ALL attributes must be equal for two books to be deemed equal.
        */
        bool operator!= (Book const &book_two) const;		

        /**
         * @param  : the title of the Book
         * @post   : sets the Book's title to the value of the parameter
        */
        void setTitle(const std::string& title);
        
        /**
         * @param  : the name of the author of the Book
         * @post   : sets the Book's author to the value of the parameter
        */        
        void setAuthor(const std::string& author);
        
        /**
         * @param  : a positive integer page count
         * @pre    : page count > 0 - books cannot have a negative number of pages
         * @post   : sets the page count to the value of the parameter
        */        
        void setPageCount(const int& page_count);

        /**
         * @post   : sets the digital flag to true
        */        
        void setDigital();

        /**
         * @return : the title of the Book
        */
        std::string getTitle() const;

        /**
         * @return : the author of the Book
        */
        std::string getAuthor() const;

        /**
         * @return : the page count
        */
        int getPageCount() const;

        /**
         * @return true if the book is available in digital form, false otherwise
        */
        bool isDigital() const;

        /**
         * @post : displays Book data in the form:
         * "[title_] is written by [author_]. Page Count: [page_count_]. [It is / It is not] available digitally.\n"
        */
        virtual void display() const = 0;

        /**
         * @param:  A reference to a string key
         * @post:   Display book data if key argument matches (key match will be subclass specific) 
        */
        virtual void displayFilter(const std::string& key) const = 0;

};

#endif
