#ifndef __ANIMATION_H
#define __ANIMATION_H

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "text_color.h"
///Struct para armazenar cada barra
struct bar{

    // time_stamp, label, other_related_info, value, category
    std::string time_stamp;///The time frame of the bar
    std::string label;///The name related to the bar
    std::string other_related_info;///Other info related to the bar
    std::string value; ///The numeric value of the bar
    std::string category; ///The category related to the bar
    short color_code; ///The color associated to the bar

    bar(std::string _time, std::string _label, std::string _other, std::string _value, std::string _category)
    {
        time_stamp = _time;
        label = _label;
        other_related_info = _other;
        value = _value;
        category = _category;
    }
};
struct chart{
    std::string Time; ///The timeframe of the chart
    std::vector<bar> carters; ///The vector of bars from the chart
    
    /// @brief Re-orders the chart's bars vector according to their values and erases any element past the maximum amount defined.
    /// @param max_bars_in_chart The max amount of bars defined.
    void no_disorder(long unsigned int max_bars_in_chart);
    
    /// @brief Prints the bars in a chart's bars vector.
    /// @param tamanho_barras The maximum lenght of a bar.
    void print(int tamanho_barras);

    /// @brief Prints the X-Axis of a chart.
    /// @param tamanho_barras The maximum lenght of the bars.
    /// @param n_ticks The amount of ticks to be printed in the X-Axis.
    void print_numberbar(int tamanho_barras, int n_ticks=6);
};
class AnimationController
{
    enum class AnimationInput { START, START_CONFIRMED };
    enum class AnimationState { START, PROCESSING, PRINTING, CONFIRM_START, ENDING, OVER };
    enum class ErrorState {NO_ERROR, INVALID_DATA_ON_THE_LINE}; 
    AnimationInput m_input = AnimationInput::START; 
    AnimationState m_state = AnimationState::START;
    std::vector<std::string> m_command_line_args;
    std::vector<chart> screens;
    std::string m_buffer; ///the input buffer
    std::vector<std::string> m_input_vect; ///the input vector
    std::string m_data_file_name;
    std::ifstream m_arquivo;
    std::string m_title;
    std::string m_description;
    std::string m_source;

    std::string input_file_name;
    int m_read_lines=0;
    int max_bars_per_chart = 5;
    int max_configurable_bars = 15;
    int default_fps = 12;
    int max_configurable_fps = 45;
    int bar_max_lenght = 50;
    int n_ticks = 5;

    int time_idx=0, label_idx=1, other_idx=2, value_idx=3, category_idx=4;
    
    /// @brief Handles the user's argv
    /// @param arguments The user's argv in a vector of strings.
    void handleargv(std::vector<std::string> arguments);
    
    /// @brief Validates the creation of a bar.
    /// @param processed_line The line that could possibly create/define a bar for a chart.
    /// @return A boolean value indicating if the bar should be created based on it's empty collumns.
    bool validate_bar(std::vector<string> processed_line);

    /// @brief 
    /// @param argc 
    /// @param argv 
    void initialize(int argc, char** argv);
    
    public:
    
    /// @brief Sets the animation's frames per second.
    /// @param fps The amount to be set.
    void set_fps(int fps){ default_fps = fps;}

    /// @brief Sets the amount of bars that a chart can have.
    /// @param bars The amount to be set.
    void set_bars(int bars){ max_bars_per_chart = bars;}

    /// @brief Reads a .ini file with configuration and sets the program's configuration based on it.
    /// @param filename .ini file path.
    void readini(std::string filename);
    
    /// @brief Sets the data file path to be read for the animation.
    /// @param file The file path to the data file.
    void setfilename(std::string file) {m_data_file_name = file;}

    /// @brief Returns if the animation is over or not.
    /// @return A boolean indicating if the current state of the animation is the one indicating the end.
    bool is_over(){ return m_state == AnimationState::OVER;}

    /// @brief Reads an input from the user and returns whether it's not empty.
    /// @param delimeter The string containing the characters that are considered to be empty.
    /// @return A boolean indicating if the input has something other than the delimiter's characters.
    bool read_input(std::string delimeter=" "); 

    /// @brief Updates the states and variables of the AnimationController class
    void update();
    /// @brief Processes the inputs for the states of the AnimationController class
    void process_events();
    ///@brief Renders the bar charts
    void render();

};
    



#endif