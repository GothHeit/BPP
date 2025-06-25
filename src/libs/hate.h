#ifndef __HATE_H
#define __HATE_H

#include <vector>
#include <string>
namespace hate {

    ///@brief Gets a string input and returns it lowercased
    ///@param orig The original string input
    ///@return A lowercased string
    std::string strtolower(std::string orig);

    ///@brief Gets a string input (most commonly a line of input) and splits it into a vector of strings
    ///@param input The line to be split
    ///@param delimiters the paramater to split the line (a space by default)
    ///@return A vector of strings with the input minus the delimiter parameter
    std::vector<std::string> split(std::string input, std::string delimiters=" \t", bool removervazios=true);

    ///@brief Cleans the beginning of the string input by removing the specified delimiter from the left side
    ///@param input The string to be cleaned
    ///@param delimiters the paramater to be removed from the left side of the string
    ///@return the cleaned version of the string
    std::string ltrim(std::string input, std::string delimiters = " \t");

    ///@brief Cleans the end of the string input by removing the specified delimiter from the right side
    ///@param input The string to be cleaned
    ///@param delimiters the paramater to be removed from the right side of the string
    ///@return the cleaned version of the string
    std::string rtrim(std::string input, std::string delimiters = " \t");

    /// @brief creates an arithmetic progression with the first and last terms of the chart
    /// @param first the first element of the A.P
    /// @param last the last element of the A.P
    /// @param middle_terms the amount of terms to be added between the first and last
    /// @return A vector of ints with the artithmetic progression
    std::vector<int> interpolate_AP(int first, int last, int middle_terms);
    
    /// @brief counts the amount of digits in a given int
    /// @param a the int to be counted
    /// @return self explanatory
    int amount_of_digits_int(int a);

     /// @brief checks if the given element is part of the vector before the specified value(it is used to draw the "|" on the X axis) 
    /// @param j the element to be searched for in the vector
    /// @param places the vector to be searched through
    /// @param i the value that limits the search for the element
    /// @return returns true if the element is in the range and false otherwise
    bool is_equal_to_in_vector(int j, std::vector<int> places, unsigned int i);

};


#endif
