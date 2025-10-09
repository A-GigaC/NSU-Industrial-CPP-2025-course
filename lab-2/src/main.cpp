#include <iostream>
#include <string>
#include <memory>
#include "regex/Parser.h"
#include "regex/Matcher.h"

/**
 * @brief Главная функция приложения
 * @return Код завершения
 */
int main() {
    try {
        // Читаем регулярное выражение из stdin
        std::string regex_pattern;
        std::getline(std::cin, regex_pattern);
        
        // Парсим регулярное выражение
        regex::Parser parser(regex_pattern);
        auto ast = parser.parse();
        
        // Создаем сопоставитель
        regex::Matcher matcher(std::move(ast));
        
        // Обрабатываем строки из stdin
        std::string line;
        while (std::getline(std::cin, line)) {
            bool result = matcher.match(line);
            std::cout << (result ? "true" : "false") << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}