#ifndef ANIMATION_H
#define ANIMATION_H

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "text_color.h"

/// Struct que representa uma barra do gráfico
struct Bar {
    std::string time_stamp;      ///< Momento da barra
    std::string label;           ///< Nome associado à barra
    std::string other_info;      ///< Outras informações
    std::string value;           ///< Valor numérico
    std::string category;        ///< Categoria da barra
    short color_code = 0;        ///< Cor associada

    Bar(std::string time, std::string lbl, std::string info, std::string val, std::string cat)
        : time_stamp(std::move(time)), label(std::move(lbl)), other_info(std::move(info)),
          value(std::move(val)), category(std::move(cat)) {}
};

/// Struct que representa um gráfico
struct Chart {
    std::string time;           ///< Timestamp do gráfico
    std::vector<Bar> bars;      ///< Vetor de barras

    void sort_and_trim(size_t max_bars);                 ///< Ordena e limita o número de barras
    void print(int max_length) const;                    ///< Imprime as barras
    void print_x_axis(int max_length, int ticks = 6) const; ///< Imprime o eixo X
};

class AnimationController {
public:
    void set_fps(int fps) { default_fps = fps; }
    void set_max_bars(int bars) { max_bars_per_chart = bars; }
    void set_data_file(const std::string& file) { data_file_name = file; }
    bool is_over() const { return state == AnimationState::OVER; }

    void read_config(const std::string& filename);
    bool read_input(const std::string& delimiters = " ");

    void update();
    void process_events();
    void render();

private:
    enum class InputState { START, START_CONFIRMED } input = InputState::START;
    enum class AnimationState { START, PROCESSING, PRINTING, CONFIRM_START, ENDING, OVER } state = AnimationState::START;
    enum class ErrorState { NO_ERROR, INVALID_DATA_LINE } error = ErrorState::NO_ERROR;

    std::vector<std::string> cmd_args;
    std::vector<Chart> frames;
    std::string input_buffer;
    std::vector<std::string> input_vector;

    std::string data_file_name;
    std::ifstream file_stream;

    std::string title;
    std::string description;
    std::string source;

    int read_lines = 0;
    int max_bars_per_chart = 5;
    int max_configurable_bars = 15;
    int default_fps = 12;
    int max_configurable_fps = 45;
    int bar_max_length = 50;
    int n_ticks = 5;

    int time_idx = 0;
    int label_idx = 1;
    int other_idx = 2;
    int value_idx = 3;
    int category_idx = 4;

    void initialize(int argc, char** argv);
    void handle_arguments(const std::vector<std::string>& args);
    bool validate_bar_data(const std::vector<std::string>& fields);
};

#endif // ANIMATION_H
