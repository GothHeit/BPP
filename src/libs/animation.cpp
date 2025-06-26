#include "hate.h"
#include "animation.h"
#include <thread>
#include <unordered_set>
#include <chrono>
#include <cmath>
#include <unordered_map>
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

void chart::no_disorder(long unsigned int max_bars_in_chart)
    {
        std::stable_sort(carters.begin(), carters.end(), [](bar a, bar b){return stod(b.value)<stod(a.value);});
        if(carters.size() > max_bars_in_chart)
        {
            carters.erase(carters.begin() + max_bars_in_chart, carters.end());
        }
    }
bool AnimationController::read_input(std::string delimiter)
{
    m_buffer.clear();
    std::getline(std::cin, m_buffer);
    m_buffer = hate::strtolower(m_buffer);
    m_input_vect=hate::split(m_buffer, delimiter);
    return !m_input_vect.empty();
}

std::unordered_set<std::string> category_set;

std::array<short, 16> cores = {Color::BLUE, Color::MAGENTA, Color::BLACK, Color::RED, Color::GREEN, Color::YELLOW,
                               Color::CYAN, Color::WHITE,
   Color::BRIGHT_BLACK, Color::BRIGHT_RED, Color::BRIGHT_GREEN, Color::BRIGHT_YELLOW,
   Color::BRIGHT_BLUE, Color::BRIGHT_MAGENTA, Color::BRIGHT_CYAN, Color::BRIGHT_WHITE};

short cat_to_color(std::string meow){
        
        
        if(category_set.size() > 14)
        {
            return cores[5];
        }
        else
        {
            int i=0;
            for(auto& cat : category_set)
            {
                if(cat == meow)
                {
                    return cores[i%(cores.size())];
                }
                i++;
            }
        }

        return cores[2];
    }


    void chart::print(int tamanho_barras)
    {
        std::cout << Time << "\n\n";
        for(bar &barra : carters){
            for(int i=0; i < std::floor(tamanho_barras/*Biggest bar size(configurable)*/ * ( stod(barra.value) / stod(carters[0].value)) ); ++i)
                std::cout << Color::tcolor("█", cat_to_color(barra.category)); // Cor depende do "grupo"
            std::cout << " " << barra.label << "(" << barra.value << ")" << "\n\n";
        }
    }
    void chart::print_numberbar(int tamanho_barras, int n_ticks){
        int minimum = tamanho_barras * ( stod(carters.back().value) / stod(carters.front().value) );
        int maximum = tamanho_barras;
        // LEMRAR DE FAZER A QUANTIDADE SER VARIÁVEL.
        std::vector<int> places = hate::interpolate_AP(minimum, maximum, n_ticks-2);
        std::vector<int> values = hate::interpolate_AP(stod(carters.back().value), stod(carters.front().value), n_ticks-2);

        int vect_iter=0;
        for(int i=0;i<1.5*tamanho_barras;i++){            
            if(i==places[vect_iter]){
                vect_iter++;
                std::cout << "+";
            }
            else if(i==1.5*tamanho_barras-1){
                std::cout << "|";
            }
            else{
                std::cout << "-";
            }
        }
        std::cout << "\n";
        //criar a função gerar na horizontal
        //if(não tem colisão)
        //criar a função gerar na vertical
        //else
        //print_vertical(tamanho_barras);
        for(int i=places.size()-1; i >= 0; i--){
            for(int j=0;j<1.5*tamanho_barras;j++){
                if(j==places[i]){
                    //std::cout << "\n"<< j << " " << places[i] << "\n";
                    std::cout << values[i];
                }
                else if(hate::is_equal_to_in_vector(j, places, i)){
                    std::cout << "|";
                }
                else std::cout << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

bool AnimationController::validate_bar(std::vector<string> processed_line){
    int a = processed_line.size();
    if(a > time_idx){
        if(processed_line[time_idx].empty()){
            return false;
        }
    }
    else{
        return false;
    }
    if(a > label_idx){
        if(processed_line[label_idx].empty()){
            return false;
        }
    }
    else{
        return false;
    }
    if(a > other_idx){
        if(processed_line[other_idx].empty()){
            return false;
        }
    }
    else{
        return false;
    }
    if(a > value_idx){
        if(processed_line[value_idx].empty())
        {
            return false;
        }
        else{
            try 
            {
                std::stoi(processed_line[value_idx]);
            }
            catch(std::invalid_argument& e){
                return false;
            }
        }
    }
    else{
        return false;
    }
    if(a > category_idx){
        if(processed_line[category_idx].empty()){
            return false;
        }
    }
    else{
        return false;
    }
    return true;
}
void AnimationController::process_events(){
    if(m_state == AnimationState::CONFIRM_START){
        read_input();
        m_input = AnimationInput::START_CONFIRMED;
    }
}
void AnimationController::render(){
    if(m_state == AnimationState::PROCESSING){
        std::string please_stand_by = R"(

                                                                                            

⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⠿⣷⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣤⣤⣴⣿⠟⠁⠀⠈⠛⠿⣿⣿⣶⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⢀⣴⣶⣇⠀⢀⣴⣿⠟⠉⠉⠙⠛⠁⠀⠀⠀⠀⠀⠀⠀⠈⠉⠻⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀,------. ,--.   ,------.  ,---.   ,---.  ,------.     ,---. ,--------. ,---.  ,--.  ,--.,------.      ,-----.,--.   ,--.⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢀⣿⡟⠙⢿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣷⣄⠀⠀⠀⠀⠀⠀|  .--. '|  |   |  .---' /  O  \ '   .-' |  .---'    '   .-''--.  .--'/  O  \ |  ,'.|  ||  .-.  \     |  |) /_\  `.'  /⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠸⣿⡇⠀⠀⠀⠀⠀⢀⡴⠶⢦⣄⣀⣤⠾⠛⠛⣧⡀⠀⠀⠀⠀⠀⠀⠈⠛⢿⣿⣄⠀⠀  |  '--' ||  |   |  `--, |  .-.  |`.  `-. |  `--,     `.  `-.   |  |  |  .-.  ||  |' '  ||  |  \  :    |  .-.  \'.    /
⢠⣿⣇⠀⠀⠀⠀⣴⠋⠀⠀⠀⠈⠉⠁⠀⠀⠀⠈⠻⣦⣤⡤⠶⠻⢿⣦⠀⠀⢻⣿⣆   |  | --' |  '--.|  `---.|  | |  |.-'    ||  `---.    .-'    |  |  |  |  | |  ||  | `   ||  '--'  /    |  '--' /  |  |
⢸⣿⠉⢳⣶⢶⡿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣿⠁⠀⠀⣿⣿⠀  `--'     `-----'`------'`--' `--'`-----' `------'    `-----'   `--'  `--' `--'`--'  `--'`-------'     `------'   `--'
⠘⣿⣄⡾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠄⠀⠀⠀⠀⢠⡼⠋   ⣿⣿⠀                                                      ⢀⣠⣤⣶⣶⣶⣿⣷⣶⣶⣦⣤⣀⡀
⠀⢹⡿⠁⠀⢀⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠠⣝⢦⡀⠀⠀⣿⣿⠀⠀⠀                                                  ⣠⡾⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠻⢶⣄
⢀⣿⠇⠀⠀⠘⣿⠇⠀⠀⢀⠎⠀⠀⠀⠘⠛⠛⠿⠆⠀⠀⠀⠀⠠⣝⢧⡳⡄⣸⣿⡟                                                   ⣠⡾⠋⠀⠀⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠀⠀⠀⠙⣷⡄
⢸⣿⠀⠀⠀⠀⠀⠀⢠⡾⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⣜⢷⣽⣷⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                      ⣰⡟⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠈⢿⡄
⢸⡏⠀⠀⠀⠀⠀⠀⢿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠆⣹⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                     ⢠⣿⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠈⣷
⢸⣇⠀⠀⠀⠀⠀⠀⠈⠛⠂⠀⠀⠀⠀⢠⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                     ⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⣠⠿⠛⠻⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡇
⢸⣿⠀⠀⣾⣤⣀⣀⣀⢀⣀⣀⣀⡤⠔⠚⢿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                    ⠀⣿⣧⣤⣤⣤⣤⣤⣤⣤⣼⡇⠀⠀⠀⠈⣿⣤⣤⣤⣤⣤⣤⣤⣤⣼⡇
⠀⣿⣇⠀⠻⠳⢤⣈⣉⠉⠉⠀⣀⣀⣤⠖⠋⠟⠀⠀⠀⠀⠀⠀⢀⣀⣠⣾⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                     ⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⣀⣀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇
⠀⠘⣿⣆⠀⠀⠀⠈⠙⣛⣛⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⠿⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                     ⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠉⠉⠉⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⡿
⠀⠀⠘⢿⣧⡀⠀⠀⠈⠛⠛⠃⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                      ⠸⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣿⣿⣿⣿⠃    
⠀⠀⠀⠈⠻⣿⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                          ⠘⢿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣿⠟⠁
⠀⠀⠀⠀⠀⠈⠙⠿⣿⣶⣦⣤⣤⣤⣤⣶⣶⣿⠿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                               ⠙⠿⣿⣇⡀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣿⣿⠟⠁
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                  ⠉⠙⠛⠿⠶⠶⠶⠾⠟⠛⠋⠉
        
>>>>> PROCESSING DATA
)";
        std::cout << Color::tcolor(please_stand_by, Color::BRIGHT_YELLOW);
        sleep_for(std::chrono::milliseconds(300));
    }
    else if(m_state == AnimationState::CONFIRM_START){
        std::cout << "                                               RUNNING OPTIONS:";
        std::cout << "\n                                      [Collumns Used For Charts Creation]\n";
        std::cout << "                                        Time: " << time_idx << '\n';
        std::cout << "                                        Name: " << label_idx << '\n';
        std::cout << "                                        Other: " << other_idx << '\n';
        std::cout << "                                        Data Value: " << value_idx << '\n';
        std::cout << "                                        Category: " << category_idx << '\n';
        
        std::cout << "\n                                                   [Charts]\n";
        std::cout << "                                        Amount of bars(max) per chart: " << max_bars_per_chart << '\n';
        std::cout << "                                        Lenght of the biggest bar(fixed): " << bar_max_lenght << '\n';
        std::cout << "\n                                                  [Animation]\n";
        std::cout << "                                        Running FPS: " << default_fps << '\n';
        std::cout << "                                        N_Ticks: " << n_ticks << '\n';
        
        int biggestsize{};
        for(auto& cat : category_set){
            int tempsize = cat.size();
            biggestsize = std::max(tempsize, biggestsize);
        }

        std::cout << "Category amount:" << category_set.size() << ' ';

        std::cout << "Category Colors:\n";
        int asd{};
        for(auto& cat : category_set){
            if(asd%5 == 0){std::cout << '\n';}
            std::cout << " " << Color::tcolor(cat, cat_to_color(cat)) << ' ';
            std::cout << " | ";
            asd++;
        }
        std::cout << "\n";
        std::cout << ">>>> We have \"" << screens.size() << "\" charts, each with a maximum of \"" << max_bars_per_chart << "\" bars.";
        std::cout << "\n";


        std::cout << ">>>>>PRESS ENTER [↵] TO CONTINUE\n";
    }
    else if(m_state == AnimationState::PRINTING){
        for(auto a: screens){
            if(a.carters.empty()){continue;}
            std::cout << m_title << "\n" << m_description << "\n";
            a.print(bar_max_lenght);
            if(n_ticks >= 2)
            {
                a.print_numberbar(bar_max_lenght, n_ticks);
            }
            if(category_set.size() <= 14)
            {
                for(auto& cat : category_set)
                {
                    std::cout << Color::tcolor("█", cat_to_color(cat)) << " " + cat << " ";
                }
            }
            std::cout << "\n\n";

            sleep_for(milliseconds(1000/default_fps));
        }
    }
}
    

void AnimationController::update(){
    if(m_state == AnimationState::START){
        m_state = AnimationState::PROCESSING;
    }
    else if(m_state == AnimationState::PROCESSING){
        m_arquivo.open(m_data_file_name);
        std::string line;
        std::vector<std::string> processed_line;            
        for(int i=0;i<3;i++){
            m_read_lines++;
            std::getline(m_arquivo >> std::ws, line);
            if(i==0){
                m_title = hate::ltrim(hate::rtrim(line));
            }
            else if(i==1){
                m_description = hate::ltrim(hate::rtrim(line));
            }
            else if(i==2){
                m_source = hate::ltrim(hate::rtrim(line));
            }
        }
        while(std::getline(m_arquivo >> std::ws, line)){
            m_read_lines++;
            chart main_chart;
            int n{};
            processed_line = hate::split(line, ",");
            n = stoi(processed_line[0]);
            //std::cout << n << "\n";
            for(int i=0; i<n; ++i)
            {
                //std::this_thread::sleep_for(std::chrono::milliseconds(50));
                //std::cout << i << "\n";
                m_read_lines++;
                std::getline(m_arquivo >> std::ws, line);
                processed_line = hate::split(line, ",");
                //checar se é valida a barra
                if(validate_bar(processed_line)){
                    bar barra
                        ( 
                            processed_line[ time_idx ]/*time*/,
                            processed_line[ label_idx ]/*label*/,
                            processed_line[ other_idx ]/*other*/,
                            processed_line[ value_idx ]/*value*/,
                            processed_line[ category_idx ]/*category*/
                        );
                    main_chart.carters.push_back(barra);
                    category_set.emplace(barra.category);
                    main_chart.Time=processed_line[time_idx];
                }
            }
            main_chart.no_disorder(max_bars_per_chart);
            screens.push_back(main_chart);
        }
        m_state = AnimationState::CONFIRM_START;
    }
    else if(m_state == AnimationState::CONFIRM_START)
    {
        if(m_input == AnimationInput::START_CONFIRMED)
        {
            m_state = AnimationState::PRINTING;
        }
    }
    else if(m_state == AnimationState::PRINTING)
    {
        m_state = AnimationState::OVER;
    }
}

void AnimationController::readini(std::string filename){
    std::unordered_map<std::string, std::string> configs;
    std::ifstream settings{filename};
            
    if(settings.is_open()){
        std::string linha;
        while(std::getline(settings, linha)){
            std::vector<std::string> coisas = hate::split(linha, "= \t");
            if(coisas.size() >= 2){
            configs[coisas[0]] = coisas[1];
            }
        }   
    }
    else
    {
        std::cerr << "Can't read .ini file. Running program with default settings.\n";
        return;
    }
    for(auto &a : configs)
    {
        if(hate::strtolower(a.first) == "defaultbars"){ max_bars_per_chart = stoi(a.second);}
        else if(hate::strtolower(a.first) == "maxbars"){ max_configurable_bars = stoi(a.second);}
        else if(hate::strtolower(a.first) == "defaultfps"){ default_fps = stoi(a.second);}
        else if(hate::strtolower(a.first) == "maxfps"){ max_configurable_fps = stoi(a.second);}
        else if(hate::strtolower(a.first) == "maxfps"){ max_configurable_fps = stoi(a.second);}
        else if(hate::strtolower(a.first) == "barmaxlenght"){ bar_max_lenght = stoi(a.second);}
        else if(hate::strtolower(a.first) == "nticks"){ n_ticks = stoi(a.second);}

        else if(hate::strtolower(a.first) == "dateidx"){ time_idx = stoi(a.second);}
        else if(hate::strtolower(a.first) == "labelidx"){ label_idx = stoi(a.second);}
        else if(hate::strtolower(a.first) == "otheridx"){ other_idx = stoi(a.second);}
        else if(hate::strtolower(a.first) == "valueidx"){ value_idx = stoi(a.second);}
        else if(hate::strtolower(a.first) == "categoryidx"){ category_idx = stoi(a.second);}
    }
}
