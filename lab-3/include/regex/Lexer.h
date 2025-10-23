#pragma once

#include <string>
#include <vector>

using namespace std;

namespace regex {

/**
 * @brief Типы токенов
 */
enum class TokenType {
    CHAR,       // Обычный символ
    DOT,        // .
    GROUP_OPEN, // [
    GROUP_CLOSE, // ]
    STAR,       // *
    PLUS,       // +
    QUESTION,   // ?
    HYPHEN,     // -
    END         // Конец входных данных
};

/**
 * @brief Токен лексического анализа
 */
struct Token {
    TokenType type;
    char value;
    
    Token(TokenType t, char v = '\0');
};

/**
 * @brief Лексический анализатор для регулярных выражений
 */
class Lexer {
private:
    string m_input;
    size_t m_position;
    
public:
    explicit Lexer(const string& input);
    
    /**
     * @brief Получает следующий токен
     * @return Токен
     */
    Token nextToken();
    
    /**
     * @brief Возвращает текущую позицию
     * @return Текущая позиция
     */
    size_t getPosition() const;
};

} // namespace regex