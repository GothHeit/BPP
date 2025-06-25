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
#include <cstdlib> // EXIT_SUCCESS
#include "libs/animation.h"
#include "libs/hate.h"
#include <filesystem> //exists
#include <chrono> //duration
#include <thread> //sleep_for
//macro para a string indefinida
// #include "bcr_am.h"
#define UNDEFINED_STRING "-#@"

struct Argument_Options{
  bool send_help=false;
  bool is_all_invalid=false;
  //"-b 60"
  int bar_argument=-1;
  //"-f 24"
  int fps_argument=-1;
  std::string ini_file = UNDEFINED_STRING;
  std::string text_file = UNDEFINED_STRING;
};
///@brief Handles the command line arguments
///@param argc the args
///@param argv the argv 
///@param options the running options

void handle_argv(int argc, char* argv[], Argument_Options &options){
  std::vector<std::string> strings;
  if(argc == 1){
    options.is_all_invalid=true;
    return;
  }
  for(int i=1; i<argc; ++i){
    strings.push_back(argv[i]);
  } 
  int str_sz=strings.size();
  for(int i=0; i<str_sz; ++i){
    if(strings[i][0] == '-'){
      if(strings[i]=="-b"){
        if(++i<str_sz){
          int b=std::stoi(strings[i]);
          if(b > 5){
            options.bar_argument=b;
          }
        }
      }
      else if(strings[i]=="-f"){
        if(++i<str_sz){
          int fps=std::stoi(strings[i]);
          if(fps > 0){
            options.fps_argument=fps;
          }
        }
      }
      else if(strings[i]=="-b"){
        if(++i<str_sz){
          int f=std::stoi(strings[i]);
          if(f > 0){
            options.bar_argument=f;
          }
        }
      }
      else if(strings[i] == "-h"){
        options.send_help=true;
        return;
      }
    }
    else{
      //é um candidato a ini
      size_t pos = strings[i].rfind('.');
      if(pos!= std::string::npos){
        std::string temp = strings[i].substr(pos);
        if(temp == ".ini"){
          if(options.ini_file == UNDEFINED_STRING){
            options.ini_file=strings[i];
          }
        }
        else{
          if(std::filesystem::exists(strings[i])){
            options.text_file=strings[i];
          }
        }
      }
      else{
        if(std::filesystem::exists(strings[i])){
            options.text_file=strings[i];
          }
      }
    }
  }
  return;
}
///prints the help text
void send_help()
{
  std::string help = R"(
  
    Welcome to the Bar Chart Race program.
    You need to provide a formated data file to run the program
    run with the following command
    ./bcr {mandatory: <DATA_FILE>} {optional: <ini file with settings>} {optional: <command line arguments}
    Command line arguments:

    -b <interger> sets the max amount of horizontal bars to be displayed
    -f <interger> sets the framerate of the program
    
    )";
  std::cout << help;
}
///@brief Handles the given options and edits the AnimationController class
///@param options the options struct
///@param animations The AnimationController class

void handle_options(const Argument_Options &options, AnimationController &animation){
  if(options.is_all_invalid){
    //help
    send_help();
    exit(1);
  }
  if(options.send_help){
    send_help();
    exit(1);
  }
  if(options.text_file != UNDEFINED_STRING){
    animation.setfilename(options.text_file); 
  }
  else{
    std::cerr << "Data file not found. Use the argument -h to learn more";
  }
  if(options.ini_file != UNDEFINED_STRING){
    animation.readini(options.ini_file); 
  }
  if(options.bar_argument!=-1){
    animation.set_bars(options.bar_argument);
  }
  if(options.fps_argument != -1){
    animation.set_fps(options.fps_argument);
  }
}

int main(int argc, char **argv) {
  Argument_Options options;

  handle_argv(argc, argv, options);

  AnimationController animation;

  handle_options(options, animation);
  

  // The Game Loop architecture or design pattern.
  while (not animation.is_over()) {
    animation.process_events();
    animation.update();
    //std::this_thread::sleep_for(std::chrono::milliseconds(50));
    animation.render();
  }

  return EXIT_SUCCESS;
}
