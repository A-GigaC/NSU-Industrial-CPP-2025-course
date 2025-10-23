#pragma once

#include <memory>
#include "Lexer.h"
#include "AST.h"

using namespace std;

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
    unique_ptr<ASTNode> parseExpression();
    
    /**
     * @brief Парсит элемент с возможными модификаторами
     * @return Узел элемента
     */
    unique_ptr<ASTNode> parseElement();
    
    /**
     * @brief Парсит базовый элемент (без модификаторов)
     * @return Узел базового элемента
     */
    unique_ptr<ASTNode> parseBaseElement();
    
    /**
     * @brief Парсит группу символов ([abc])
     * @return Узел группы
     */
    unique_ptr<ASTNode> parseGroup();
    
public:
    explicit Parser(const string& input);
    
    /**
     * @brief Парсит регулярное выражение
     * @return Корневой узел AST
     * @throws runtime_error при синтаксической ошибке
     */
    unique_ptr<ASTNode> parse();
};

} // namespace regex