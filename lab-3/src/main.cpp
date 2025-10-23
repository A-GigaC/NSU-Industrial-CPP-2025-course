#include <iostream>
#include <string>
#include <memory>
#include "regex/Parser.h"
#include "regex/Matcher.h"

using namespace regex;
using namespace std;


/**
 * @brief Главная функция приложения
 * @return Код завершения
 */
int main() {
    try {
        // Читаем регулярное выражение из stdin
        string regex_pattern;
        getline(cin, regex_pattern);
        
        // Парсим регулярное выражение
        Parser parser(regex_pattern);
        auto ast = parser.parse();
        
        // Создаем мэтчер
        Matcher matcher(move(ast));
        
        // Обрабатываем строки из stdin
        string line;
        while (getline(cin, line)) {
            bool result = matcher.match(line);
            cout << (result ? "true" : "false") << endl;
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}