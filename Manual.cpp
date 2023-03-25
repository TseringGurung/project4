#ifndef MANUAL_HPP_
#define MANUAL_HPP_

#include "Book.hpp"

/**
 * @param   : a website url
 * @return  : returns true/false depending on the website url
 *              following the format 'https://www.something.something'
 *              or 'http://www.something.something' with the last 
 *              'something' being at least 2 characters
*/
bool isValidURL(std::string url);

class Manual : public Book {
    private:
        std::string website_url_;   // a string that represents a url.
        std::string device_name_;   // a string that represents the name of the device.
        bool has_visual_aid_;       // a boolean indicating whether the Manual has a visual aid.
        bool has_website_;          // a boolean indicating whether the Manual has a website.

    public:
        /**
         * Default constructor.
         * Default-initializes all private members.
        */
        Manual()=default;

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
        Manual(std::string title, std::string author, int page_count, std::string device_name, bool is_digital=false, std::string website_url="", bool has_visual_aid=false);

        /**
            * @param    : a refrence to a string representing the device.
            * @post     : sets the private member variable to the value of the parameter.
        */
        void setDevice(const std::string& device);

        /**
         * @return    : the variable indicated the device the manual is for.
         */
        std::string getDevice() const;

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
        bool setWebsite(const std::string& website_link);

        /**
         * @return  : the url for the website.
        */
        std::string getWebsite() const;

        /**
         * @param   : a boolean
         * @post    : sets the private member variable indicating the presence
         *              of a visual aid to the value of the parameter.
        */
        void setVisualAid(const bool& has_visual_aid);

        /**
         * @return  : the visual aid flag.
        */
        bool hasVisualAid() const;

        /**
         * @return  : the has website flag.
        */
        bool hasWebsite() const;

        /**
         * @post     : displays Manual data in the form:
         * "[title_] is written by [author] company for device: [device]. Website: [website / NONE]. Page Count: [page_count_]. [It is / It is not] available digitally.\n"  
         */
        void display() const;

        /**
         * @param    : a reference to a string key to match the device of the Manual
         * @post     : calls display() if the key argument is equal to device_ (e.g. "Oven")   
         */
        void displayFilter(const std::string& key) const;

};

#endif
