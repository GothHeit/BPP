#include "hate.h"


    ///@brief Gets a string input and returns it lowercased
    ///@param orig The original string input
    ///@return A lowercased string
    std::string hate::strtolower(std::string orig)
    {
        int n = orig.size();
        for(int i=0; i<n; ++i)
        {
            orig[i] = tolower(orig[i]);
        }
        return orig;
    }

    ///@brief Gets a string input (most commonly a line of input) and splits it into a vector of strings
    ///@param input The line to be split
    ///@param delimiters the paramater to split the line (a space by default)
    ///@return A vector of strings with the input minus the delimiter parameter
    std::vector<std::string> hate::split(std::string input, std::string delimiters, bool removervazios)
    {
        std::vector<std::string> out{};
        std::string calma{};
        int size = input.size();
        for(int i=0; i<size; ++i)
        {
            if(delimiters.find(input[i])==std::string::npos)
            {
                calma+=input[i];        
                if(i==size-1)
                {
                    out.push_back(calma);
                } 
            }
            else
            {
                if(!removervazios || calma.size() > 0)
                {
                out.push_back(calma);
                }
                calma.clear();
                if(i == size-1 && !removervazios){
                    out.push_back("");
                }
            }
        }
        return out;    
    }


    ///@brief Cleans the beginning of the string input by removing the specified delimiter from the left side
    ///@param input The string to be cleaned
    ///@param delimiters the paramater to be removed from the left side of the string
    ///@return the cleaned version of the string
    std::string hate::ltrim(std::string input, std::string delimiters)
    {
        int indice=0;
        for(char a : input){
            if(delimiters.find(a) == std::string::npos)
            {
                break; 
            }
            indice++;
        }
        return input.substr(indice);
    }

    ///@brief Cleans the end of the string input by removing the specified delimiter from the right side
    ///@param input The string to be cleaned
    ///@param delimiters the paramater to be removed from the right side of the string
    ///@return the cleaned version of the string
    std::string hate::rtrim(std::string input, std::string delimiters)
    {
        for(int indice = input.size()-1; indice>=0; indice--)
        {
            if(delimiters.find(input[indice]) == std::string::npos)
            {
                return input.substr(0, indice+1);
            }
        }
        return input.substr(0, 0);
    }
    /// @brief creates an arithmetic progression with the first and last terms of the chart
    /// @param first the first element of the A.P
    /// @param last the last element of the A.P
    /// @param middle_terms the amount of terms to be added between the first and last
    /// @return A vector of ints with the artithmetic progression
    std::vector<int> hate::interpolate_AP(int first, int last, int middle_terms){
        std::vector<int> result;
        float mean = (last-first)/float(middle_terms+1);
        //std::cout << mean << "\n";
        for(int i=0;i<middle_terms+2;i++){
            result.push_back(first+i*mean);
        } 
        //std::cout << middle_terms+2 << "\n";
    return result;
    }

    /// @brief counts the amount of digits in a given int
    /// @param a the int to be counted
    /// @return self explanatory
    int hate::amount_of_digits_int(int a){
        if(a==0){
            return 1;
        }
        else{
            int result=0;
            while(a>0){
                result++;
                a/=10;
            }
            return result;
        }
    }
    
    /// @brief checks if the given element is part of the vector before the specified value(it is used to draw the "|" on the X axis) 
    /// @param j the element to be searched for in the vector
    /// @param places the vector to be searched through
    /// @param i the value that limits the search for the element
    /// @return returns true if the element is in the range and false otherwise
    bool hate::is_equal_to_in_vector(int j, std::vector<int> places, unsigned int i){
        for(unsigned int k=0;k<places.size();k++){
            if(j == places[k] and i>k){
                return true;
            }
        }
        return false;
    }