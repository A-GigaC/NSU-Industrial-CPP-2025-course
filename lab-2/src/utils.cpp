#include "utils.h"
#include <sstream>

namespace utils {

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

bool isInRange(char c, char start, char end) {
    return c >= start && c <= end;
}

} // namespace utils