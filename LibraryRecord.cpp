#include "LibraryRecord.hpp"
#include "Textbook.hpp"
#include "Manual.hpp"
#include "Novel.hpp"

/** default constructor**/
LibraryRecord::LibraryRecord() : ArrayBag<Book*>()
{
}

/* parameterized constructor
Implement a parameterized constructor that takes the name of the input file as a reference to string argument. 
The constructor will read the input file, where each line corresponds to a Book subclass and 
dynamically allocate Book-derived objects with the information read from the input file and add them to the LibraryRecord.
  Each line in the input file has the following format:
  title, author, page_count, is_digital, genre, subject, grade_level, has_film_adaptation, has_review_questions, device_model, website, book_type
The 3 class types are listed as book_type and are:
Novel (represented by 1)
Textbook (represented by 2)
Manual (represented by 3)

*/
LibraryRecord::LibraryRecord(const std::string& input_file){
  std::string type, title_file, author_file, page_count_file, is_digital_file, genre_file, subject_file, grade_level_file, has_film_file, has_review_file, device_model_file, website_file, book_type_file;
  std::ifstream book_file(input_file);
  if(!book_file.is_open()){
    std::cout << "Error\n";
  }
  std::getline(book_file, type, '\n');
  while(book_file.good()){
    std::getline(book_file, title_file, ',');
    std::getline(book_file, author_file, ',');
    std::getline(book_file, page_count_file, ',');
    std::getline(book_file, is_digital_file, ',');
    std::getline(book_file, genre_file, ',');
    std::getline(book_file, subject_file, ',');
    std::getline(book_file, grade_level_file, ',');
    std::getline(book_file, has_film_file, ',');
    std::getline(book_file, has_review_file, ',');
    std::getline(book_file, device_model_file, ',');
    std::getline(book_file, website_file, ',');
    std::getline(book_file, book_type_file, ',');

    if(book_type_file == "1"){
      Novel* novel_ = new Novel(title_file, author_file, std::stoi(page_count_file), genre_file, std::stoi(is_digital_file),std::stoi(has_film_file));
      add(novel_);
    }
    if(book_type_file == "2"){
      Textbook* textbook_ = new Textbook(title_file, author_file, std::stoi(page_count_file), std::stoi(is_digital_file), subject_file, stringGrade(grade_level_file), std::stoi(has_review_file));
      add(textbook_);
    }
    if(book_type_file == "3"){
      Manual* manual_ = new Manual(title_file, author_file, std::stoi(page_count_file), std::stoi(is_digital_file), device_model_file, website_file);
      add(manual_);
    }
  }
}



/** @param:   A reference to a Book object to be checked in
    @return:  returns true if a book was successfully added to items, false otherwise
    @post:    adds book to items.
 **/
bool LibraryRecord::checkIn(Book* new_entry)
{
  if(add(new_entry)){
    return true;
  }
  return false;
}

/** @param:   A reference to a Book object to be checked out   
    @return:  returns true if a book was successfully removed from items_, false otherwise
    @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the check_out_history_ vector.
 **/
bool LibraryRecord::checkOut(Book* an_entry)
{
  if(remove(an_entry)) {
      check_out_history_.push_back(an_entry);
      return true;
  }
  return false;
}

/**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been checked out

      For each Book in the LibraryRecord you will output:
             [title_] is written by [author_]. Page Count: [page_count_]. [it is / is not] available digitally.\n
             It has been checked out [_] times.
**/
void LibraryRecord::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    int count = getCheckOutHistory(items_[i]);
    items_[i]->display();
    std::cout << "It has been checked out " << count << " times." << std::endl;
  }
}

/*Implement LibraryRecord::displayFilter that takes a reference to string key and displays information of its holdings
 whenever they key matches the relevant information (specific to the type of book).*/

void LibraryRecord::dispalyFilter(const std::string &key){
  for(int i = 0; i < item_count_; i++){
    items_[i]->displayFilter(key);
  }
} 

/**
  @post:    Prints the title of each Book in the LibraryRecord
  Example:
  "title1, title2, title3, title4!" Note the commas and exclamation mark.
*/
void LibraryRecord::displayTitles()
{
  for (int i = 0; i < item_count_; i++)
  {
    if (i < item_count_ - 1)
    {
      std::cout << items_[i]->getTitle() << ", ";
    }
    else
    {
      std::cout << items_[i]->getTitle() << "!\n";
    }
  }
}

/**
  @param:   A reference to a Book object
  @return:  The number of times (int) the referenced Book has been checked out
*/
int LibraryRecord::getCheckOutHistory(Book* an_entry)
{
  int count = 0;

  for (int j = 0; j < check_out_history_.size(); j++)
  {
    if (check_out_history_[j] == an_entry)
    {
      count++;
    }
  }
  return count;
}



/** @param:   A reference to another ArrayBag object
      @post:    Combines the contents from both ArrayBag objects, EXCLUDING duplicates.
      Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]

      IMPORTANT: We are carrying over the amount of times a book has been checked out.
      If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
      Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
void LibraryRecord::operator/=(LibraryRecord& a_library_record)
{
  int index = 0;
  int itemsToAdd = a_library_record.item_count_;
  while (itemsToAdd > 0)
  {
    if (this->item_count_ == DEFAULT_CAPACITY)
    {
      break;
    }
    if (contains(a_library_record.items_[index]))
    {
      break;
    }
    this->checkIn(a_library_record.items_[index]);
    int counter = a_library_record.getCheckOutHistory(a_library_record.items_[index]);
    for (int i = 0; i < counter; i++)
    {
      check_out_history_.push_back(a_library_record.items_[index]);
    }
    index++;
    itemsToAdd--;
  }
}


 /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
void LibraryRecord::operator+=(LibraryRecord& a_library_record)
{
  int index = 0;
  int itemsToAdd = a_library_record.item_count_;
  while (itemsToAdd > 0)
  {
    if (this->item_count_ == DEFAULT_CAPACITY)
    {
      break;
    }
    this->checkIn(a_library_record.items_[index]);
    int counter = a_library_record.getCheckOutHistory(a_library_record.items_[index]);
    for (int i = 0; i < counter; i++)
    {
      check_out_history_.push_back(a_library_record.items_[index]);
    }
    index++;
    itemsToAdd--;
  }
}


 /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
std::vector<Book*> LibraryRecord::toVector()
{
  std::vector<Book*> bag_contents;
  for (int i = 0; i < item_count_; i++)
    bag_contents.push_back(items_[i]);

  return bag_contents;
}

/**
  @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
  @post:      Duplicates all the items in the LibraryRecord
  Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
bool LibraryRecord::duplicateStock()
{
  if (item_count_ * 2 > DEFAULT_CAPACITY)
  {
    return false;
  }

  for (int i = 0; i < item_count_; i++)
  {
    items_[i + item_count_] = items_[i];
  }
  item_count_ = item_count_ * 2;
  return true;
}

/**
  @param:   A reference to a book
  @return: True or false depending on whether or not an item was removed
  @post: remove all elements of that book
*/
bool LibraryRecord::removeStock(Book* an_entry)
{
  while(remove(an_entry));
  return true;
}

/**
  @param:   A reference to another LibraryRecord
  @return:  Returns true if the 2 library records have the contents, regardless of their order. 
            For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
            and those of the referenced LibraryRecord are [book3, book1, book2], it will return true
*/
bool LibraryRecord::equivalentRecords(LibraryRecord& a_library_record)
{
  bool result = true;

  //copy contents to count duplicates by marking them as empty
  // use copy because should not modify items_
  std::vector<Book*> library_copy = toVector();
  std::vector<Book*> other_copy = a_library_record.toVector();
  Book* empty;

  for (int i = 0; i < library_copy.size(); i++)
  {
    for (int j = 0; j < other_copy.size(); j++)
    {
      if (other_copy[j] != empty && other_copy[j] == library_copy[i])
      {
        library_copy[i] = empty;
        other_copy[j] = empty;
      }
    }
  }
  //check that all entries have been accounted for
  // i.e. there are no non-empty left
  for (int i = 0; i < item_count_; i++)
  {
    if (library_copy[i] != empty)
    {
      result = false;
    }
  }
  //check that all entries have been accounted for
  // i.e. there are no non-empty left
  for (int i = 0; i < a_library_record.item_count_; i++)
  {
    if (other_copy[i] != empty)
    {
      result = false;
    }
  }
  return result;
}
