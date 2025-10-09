#pragma once

#include <memory>
#include "Lexer.h"
#include "AST.h"

namespace regex {

/**
 * @brief Синтаксический анализатор для регулярных выражений
 */
class Parser {
private:
    Lexer m_lexer;
    Token m_currentToken;
    
    /**
     * @brief Переходит к следующему токену
     */
    void advance();
    
    /**
     * @brief Парсит выражение (последовательность)
     * @return Узел последовательности
     */
    std::unique_ptr<ASTNode> parseExpression();
    
    /**
     * @brief Парсит элемент с возможными модификаторами
     * @return Узел элемента
     */
    std::unique_ptr<ASTNode> parseElement();
    
    /**
     * @brief Парсит базовый элемент (без модификаторов)
     * @return Узел базового элемента
     */
    std::unique_ptr<ASTNode> parseBaseElement();
    
    /**
     * @brief Парсит группу символов ([abc])
     * @return Узел группы
     */
    std::unique_ptr<ASTNode> parseGroup();
    
public:
    explicit Parser(const std::string& input);
    
    /**
     * @brief Парсит регулярное выражение
     * @return Корневой узел AST
     * @throws std::runtime_error при синтаксической ошибке
     */
    std::unique_ptr<ASTNode> parse();
};

} // namespace regex