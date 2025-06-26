/** @file main.cpp
 *
 * @description
 * This program implements a bar char race animation.
 *
 * ===========================================================================
 * @license
 *
 * This file is part of BAR_CHART_RACE project.
 *
 * BAR_CHART_RACE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BAR_CHART_RACE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BARCHART RACE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2021-2024 Selan R. dos Santos.
 * ===========================================================================
 *
 * @author	Selan R dos Santos, <selan.santos@ufrn.br>
 * @date	2021
 *
 * @remark On 2021-09-19 changed ...
 */
#include <cstdlib>       // EXIT_SUCCESS
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>    // std::filesystem::exists
#include <thread>        // std::this_thread::sleep_for
#include <chrono>        // std::chrono::milliseconds

#include "libs/animation.h"
#include "libs/hate.h"

#define UNDEFINED_STRING "-#@"

struct ArgumentOptions {
    bool send_help = false;
    bool is_all_invalid = false;
    int bar_argument = -1;
    int fps_argument = -1;
    std::string ini_file = UNDEFINED_STRING;
    std::string text_file = UNDEFINED_STRING;
};

void print_help() {
    const std::string help = R"(
    Welcome to the Bar Chart Race program.

    You need to provide a formatted data file to run the program.
    Run with the following command:
      ./bcr <DATA_FILE> [ini_file] [command line arguments]

    Command line arguments:
      -b <integer>  Sets the max number of horizontal bars to be displayed (must be > 5)
      -f <integer>  Sets the framerate of the program (must be > 0)
      -h            Displays this help message
    )";
    std::cout << help << '\n';
}

void handle_arguments(int argc, char* argv[], ArgumentOptions& options) {
    if (argc == 1) {
        options.is_all_invalid = true;
        return;
    }

    std::vector<std::string> args(argv + 1, argv + argc);

    for (size_t i = 0; i < args.size(); ++i) {
        const std::string& arg = args[i];

        if (arg[0] == '-') {
            if (arg == "-b" && i + 1 < args.size()) {
                try {
                    int bars = std::stoi(args[++i]);
                    if (bars > 5) {
                        options.bar_argument = bars;
                    }
                } catch (...) { /* silently ignore */ }
            }
            else if (arg == "-f" && i + 1 < args.size()) {
                try {
                    int fps = std::stoi(args[++i]);
                    if (fps > 0) {
                        options.fps_argument = fps;
                    }
                } catch (...) { /* silently ignore */ }
            }
            else if (arg == "-h") {
                options.send_help = true;
                return;
            }
            else {
                options.is_all_invalid = true;
            }
        } 
        else {
            const auto dot_pos = arg.rfind('.');
            if (dot_pos != std::string::npos && arg.substr(dot_pos) == ".ini") {
                if (options.ini_file == UNDEFINED_STRING) {
                    options.ini_file = arg;
                }
            } else if (std::filesystem::exists(arg)) {
                options.text_file = arg;
            }
        }
    }
}

void apply_options(const ArgumentOptions& options, AnimationController& animation) {
    if (options.is_all_invalid || options.send_help) {
        print_help();
        exit(1);
    }

    if (options.text_file != UNDEFINED_STRING) {
        animation.setfilename(options.text_file);
    } else {
        std::cerr << "Data file not found. Use the argument -h to learn more.\n";
        exit(1);
    }

    if (options.ini_file != UNDEFINED_STRING) {
        animation.readini(options.ini_file);
    }
    if (options.bar_argument != -1) {
        animation.set_bars(options.bar_argument);
    }
    if (options.fps_argument != -1) {
        animation.set_fps(options.fps_argument);
    }
}

int main(int argc, char** argv) {
    ArgumentOptions options;
    handle_arguments(argc, argv, options);

    AnimationController animation;
    apply_options(options, animation);

    // Game loop
    while (!animation.is_over()) {
        animation.process_events();
        animation.update();
        animation.render();
    }

    return EXIT_SUCCESS;
}
