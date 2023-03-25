//Tsering Gurung
//CS 235
//Project 4: Polymorphism
#include "Manual.hpp"

/**
 * @param   : a website url
 * @return  : returns true/false depending on the website url
 *              following the format 'https://www.something.something'
 *              or 'http://www.something.something' with the last 
 *              'something' being at least 2 characters
*/
bool isValidURL(std::string url) {
    if(url.substr(0, 12) == "https://www.") url = url.substr(12);
    else if(url.substr(0, 11) == "http://www.") url = url.substr(11);
    else return false;

    if(url.find_first_of('.') != 0) url = url.substr(url.find_first_of('.') + 1);
    else return false;

    if(url.length() < 2) return false;

    return true;
}

/**
 * Parameterized constructor.
 * @param     : The title of the book (a string)
 * @param     : The author of the book (a string)
 * @param     : The number of pages in the book (a positive integer)
 * @param     : The name of the device (a string)
 * @param     : A flag indicating whether the book is in digital form
 *               with DEFAULT VALUE False (a Boolean)
 * @param     : The URL that is in the format
 *              'https://www.something.something'
 *               or 'http://www.something.something'
 *               with the last 'something' being at least 2 characters
 *               with DEFAULT VALUE empty string (a string)
 * @param     : A Boolean indicating the presence of a visual aid
 *               with DEFAULT VALUE False
 * @post      : The private members are set to the values of the
 *               corresponding parameters.
 *               If a URL is provided, the website flag is set to True.
 *               If the URL is ill-formatted, the website is set to
 *               empty string and the website flag is set to False.
*/
Manual::Manual(std::string title, std::string author, int page_count, std::string device_name, bool is_digital, std::string website_url, bool has_visual_aid) :
    Book(title, author, page_count, is_digital),
    device_name_(device_name),
    website_url_(website_url),
    has_visual_aid_(has_visual_aid) {
        if(website_url != "" && isValidURL(website_url))
            setWebsite(website_url);
        else {
            website_url_ = ""; 
            has_website_ = false;
        }
}

/**
    * @param    : a refrence to a string representing the device.
    * @post     : sets the private member variable to the value of the parameter.
*/
void Manual::setDevice(const std::string& device){
    device_name_ = device;
}

/**
 * @return    : the variable indicated the device the manual is for.
 */
std::string Manual::getDevice() const {
    return device_name_;
}

/**
 * @param  : a reference to a website link (string) that is in the format
 *             'https://www.something.something' 
 *              or 'http://www.something.something'
 *              with the last 'something' being at least 2 characters.
 * @return : has_website_ flag (a boolean)
 * @post   : If the link is not correctly formatted,
 *             store "Broken Link" in the link member variable (see <regex>)
 *             and either way set the has website flag to True
 */
bool Manual::setWebsite(const std::string& website_link) {
    if(!isValidURL(website_link)) website_url_ = "Broken Link";
    else website_url_ = website_link;

    has_website_ = true;

    return has_website_;
}

/**
 * @return  : the url for the website.
*/
std::string Manual::getWebsite() const {
    return website_url_;
}

/**
 * @param   : a boolean
 * @post    : sets the private member variable indicating the presence
 *              of a visual aid to the value of the parameter.
*/
void Manual::setVisualAid(const bool& has_visual_aid) {
    has_visual_aid_ = has_visual_aid;
}

/**
 * @return  : the visual aid flag.
*/
bool Manual::hasVisualAid() const {
    return has_visual_aid_;
}

/**
 * @return  : the has website flag.
*/
bool Manual::hasWebsite() const {
    return has_website_;
}

/**
 * @post     : displays Manual data in the form:
 * "[title_] is written by [author] company for device: [device]. Website: [website / NONE]. Page Count: [page_count_]. [It is / It is not] available digitally.\n"  
 */
void Manual::display() const {
    std::cout << getTitle() << " is written by " << getAuthor() << " company for device: " << getDevice() << ". Website: " << (hasWebsite() ? getWebsite() : "NONE") << ". Page Count: " << getPageCount() << ". " << (isDigital() ? "It is" : "It is not") << " available digitally.\n";

}

/**
 * @param    : a reference to a string key to match the device of the Manual
 * @post     : calls display() if the key argument is equal to device_ (e.g. "Oven")   
 */
void Manual::displayFilter(const std::string& key) const {
    if (key == device_name_.substr(0, device_name_.find('-'))) display();
}
