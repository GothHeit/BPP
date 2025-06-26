#include "hate.h"
#include <cctype>  // para tolower

namespace hate {

std::string to_lower(std::string str) {
    for (char& c : str)
        c = std::tolower(static_cast<unsigned char>(c));
    return str;
}

std::vector<std::string> split(const std::string& input, const std::string& delimiters, bool remove_empty) {
    std::vector<std::string> result;
    std::string temp;

    for (size_t i = 0; i < input.size(); ++i) {
        if (delimiters.find(input[i]) == std::string::npos) {
            temp += input[i];
            if (i == input.size() - 1 && (!remove_empty || !temp.empty()))
                result.push_back(temp);
        } else {
            if (!remove_empty || !temp.empty())
                result.push_back(temp);
            temp.clear();
            if (i == input.size() - 1 && !remove_empty)
                result.push_back("");
        }
    }

    return result;
}

std::string ltrim(const std::string& input, const std::string& delimiters) {
    size_t start = 0;
    while (start < input.size() && delimiters.find(input[start]) != std::string::npos)
        ++start;
    return input.substr(start);
}

std::string rtrim(const std::string& input, const std::string& delimiters) {
    if (input.empty()) return "";

    size_t end = input.size();
    while (end > 0 && delimiters.find(input[end - 1]) != std::string::npos)
        --end;
    return input.substr(0, end);
}

std::vector<int> interpolate_arithmetic(int first, int last, int middle_terms) {
    std::vector<int> result;
    if (middle_terms < 0) return result;

    double step = static_cast<double>(last - first) / (middle_terms + 1);
    for (int i = 0; i <= middle_terms + 1; ++i)
        result.push_back(static_cast<int>(first + i * step));
    return result;
}

int count_digits(int value) {
    if (value == 0) return 1;

    int count = 0;
    while (value != 0) {
        ++count;
        value /= 10;
    }
    return count;
}

bool exists_before(const std::vector<int>& values, int target, unsigned int limit) {
    for (unsigned int k = 0; k < values.size(); ++k) {
        if (values[k] == target && k < limit)
            return true;
    }
    return false;
}

} // namespace hate
