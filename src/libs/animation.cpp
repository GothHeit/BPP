#include "hate.h"
#include "animation.h"
#include <thread>
#include <unordered_set>
#include <chrono>
#include <cmath>
#include <unordered_map>
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

void chart::no_disorder(size_t max_bars_in_chart)
{
    // Ordena em ordem decrescente baseado no valor convertido para double
    std::stable_sort(carters.begin(), carters.end(),
        [](const bar& a, const bar& b) {
            return std::stod(b.value) < std::stod(a.value);
        });

    if (carters.size() > max_bars_in_chart)
    {
        carters.erase(carters.begin() + max_bars_in_chart, carters.end());
    }
}

bool AnimationController::read_input(const std::string& delimiter)
{
    m_buffer.clear();
    if (!std::getline(std::cin, m_buffer))
        return false;

    m_buffer = hate::strtolower(m_buffer);
    m_input_vect = hate::split(m_buffer, delimiter);
    return !m_input_vect.empty();
}

static std::unordered_set<std::string> category_set;

static constexpr std::array<short, 16> cores = {
    Color::BLUE, Color::MAGENTA, Color::BLACK, Color::RED, Color::GREEN,
    Color::YELLOW, Color::CYAN, Color::WHITE,
    Color::BRIGHT_BLACK, Color::BRIGHT_RED, Color::BRIGHT_GREEN, Color::BRIGHT_YELLOW,
    Color::BRIGHT_BLUE, Color::BRIGHT_MAGENTA, Color::BRIGHT_CYAN, Color::BRIGHT_WHITE
};

short cat_to_color(const std::string& category)
{
    if (category_set.size() > 14)
        return cores[5]; // Retorna amarelo fixo se categorias são muitas

    int i = 0;
    for (const auto& cat : category_set)
    {
        if (cat == category)
            return cores[i % cores.size()];
        ++i;
    }
    return cores[2]; // Preto como fallback
}

void chart::print(int max_bar_length)
{
    std::cout << Time << "\n\n";

    if (carters.empty()) return;

    const double max_value = std::stod(carters[0].value);

    for (const bar& barra : carters)
    {
        double val = std::stod(barra.value);
        int bar_length = static_cast<int>(std::floor(max_bar_length * (val / max_value)));

        for (int i = 0; i < bar_length; ++i)
            std::cout << Color::tcolor("█", cat_to_color(barra.category));

        std::cout << " " << barra.label << " (" << barra.value << ")\n\n";
    }
}
   void chart::print_numberbar(int tamanho_barras, int n_ticks)
{
    if (carters.empty() || n_ticks < 2) return;

    double min_value = std::stod(carters.back().value);
    double max_value = std::stod(carters.front().value);

    int minimum = static_cast<int>(tamanho_barras * (min_value / max_value));
    int maximum = tamanho_barras;

    // Calcula posições e valores interpolados da escala
    std::vector<int> places = hate::interpolate_AP(minimum, maximum, n_ticks - 2);
    std::vector<int> values = hate::interpolate_AP(static_cast<int>(min_value), static_cast<int>(max_value), n_ticks - 2);

    int vect_iter = 0;
    const int total_length = static_cast<int>(1.5 * tamanho_barras);

    // Linha da barra com ticks
    for (int i = 0; i < total_length; ++i)
    {
        if (vect_iter < static_cast<int>(places.size()) && i == places[vect_iter])
        {
            std::cout << "+";
            vect_iter++;
        }
        else if (i == total_length - 1)
        {
            std::cout << "|";
        }
        else
        {
            std::cout << "-";
        }
    }
    std::cout << "\n";

    // Impressão vertical dos valores e linhas auxiliares '|'
    for (int i = static_cast<int>(places.size()) - 1; i >= 0; --i)
    {
        for (int j = 0; j < total_length; ++j)
        {
            if (j == places[i])
            {
                std::cout << values[i];
            }
            else if (hate::is_equal_to_in_vector(j, places, i))
            {
                std::cout << "|";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool AnimationController::validate_bar(const std::vector<std::string>& processed_line)
{
    auto is_valid_index = [&](int idx) {
        return idx < static_cast<int>(processed_line.size()) && !processed_line[idx].empty();
    };

    if (!is_valid_index(time_idx)) return false;
    if (!is_valid_index(label_idx)) return false;
    if (!is_valid_index(other_idx)) return false;

    if (!is_valid_index(value_idx)) return false;
    try
    {
        std::stoi(processed_line[value_idx]);
    }
    catch (const std::invalid_argument&)
    {
        return false;
    }

    if (!is_valid_index(category_idx)) return false;

    return true;
}void chart::print_numberbar(int tamanho_barras, int n_ticks)
{
    if (carters.empty() || n_ticks < 2) return;

    double min_value = std::stod(carters.back().value);
    double max_value = std::stod(carters.front().value);

    int minimum = static_cast<int>(tamanho_barras * (min_value / max_value));
    int maximum = tamanho_barras;

    // Calcula posições e valores interpolados da escala
    std::vector<int> places = hate::interpolate_AP(minimum, maximum, n_ticks - 2);
    std::vector<int> values = hate::interpolate_AP(static_cast<int>(min_value), static_cast<int>(max_value), n_ticks - 2);

    int vect_iter = 0;
    const int total_length = static_cast<int>(1.5 * tamanho_barras);

    // Linha da barra com ticks
    for (int i = 0; i < total_length; ++i)
    {
        if (vect_iter < static_cast<int>(places.size()) && i == places[vect_iter])
        {
            std::cout << "+";
            vect_iter++;
        }
        else if (i == total_length - 1)
        {
            std::cout << "|";
        }
        else
        {
            std::cout << "-";
        }
    }
    std::cout << "\n";

    // Impressão vertical dos valores e linhas auxiliares '|'
    for (int i = static_cast<int>(places.size()) - 1; i >= 0; --i)
    {
        for (int j = 0; j < total_length; ++j)
        {
            if (j == places[i])
            {
                std::cout << values[i];
            }
            else if (hate::is_equal_to_in_vector(j, places, i))
            {
                std::cout << "|";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool AnimationController::validate_bar(const std::vector<std::string>& processed_line)
{
    auto is_valid_index = [&](int idx) {
        return idx < static_cast<int>(processed_line.size()) && !processed_line[idx].empty();
    };

    if (!is_valid_index(time_idx)) return false;
    if (!is_valid_index(label_idx)) return false;
    if (!is_valid_index(other_idx)) return false;

    if (!is_valid_index(value_idx)) return false;
    try
    {
        std::stoi(processed_line[value_idx]);
    }
    catch (const std::invalid_argument&)
    {
        return false;
    }

    if (!is_valid_index(category_idx)) return false;

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
