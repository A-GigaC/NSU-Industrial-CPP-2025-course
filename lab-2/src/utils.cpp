#include "utils.h"
#include <sstream>

using namespace std;


namespace utils {

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

bool isInRange(char c, char start, char end) {
    return c >= start && c <= end;
}

} // namespace utils