#include "regex/Parser.h"
#include "utils.h"
#include <stdexcept>

using namespace regex;

Parser::Parser(const std::string& input) 
    : m_lexer(input), m_currentToken(m_lexer.nextToken()) {}

void Parser::advance() {
    m_currentToken = m_lexer.nextToken();
}

std::unique_ptr<ASTNode> Parser::parse() {
    return parseExpression();
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto sequence = std::make_unique<SequenceNode>();
    
    while (m_currentToken.type != TokenType::END) {
        auto element = parseElement();
        if (element) {
            sequence->addNode(std::move(element));
        }
    }
    
    return sequence;
}

std::unique_ptr<ASTNode> Parser::parseElement() {
    auto node = parseBaseElement();
    
    // Проверяем модификаторы
    if (m_currentToken.type == TokenType::STAR || 
        m_currentToken.type == TokenType::PLUS || 
        m_currentToken.type == TokenType::QUESTION) {
        
        char modifier = '\0';
        switch (m_currentToken.type) {
            case TokenType::STAR: modifier = '*'; break;
            case TokenType::PLUS: modifier = '+'; break;
            case TokenType::QUESTION: modifier = '?'; break;
            default: break;
        }
        
        advance(); // consume modifier
        return std::make_unique<ModifierNode>(std::move(node), modifier);
    }
    
    return node;
}

std::unique_ptr<ASTNode> Parser::parseBaseElement() {
    switch (m_currentToken.type) {
        case TokenType::CHAR: {
            auto node = std::make_unique<CharNode>(m_currentToken.value);
            advance();
            return node;
        }
        
        case TokenType::DOT: {
            auto node = std::make_unique<AnyCharNode>();
            advance();
            return node;
        }
        
        case TokenType::GROUP_OPEN: {
            return parseGroup();
        }
        
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::unique_ptr<ASTNode> Parser::parseGroup() {
    advance(); // consume '['
    
    auto group = std::make_unique<GroupNode>();
    bool in_range = false;
    char range_start = '\0';
    
    while (m_currentToken.type != TokenType::GROUP_CLOSE) {
        if (m_currentToken.type == TokenType::END) {
            throw std::runtime_error("Unclosed group");
        }
        
        if (m_currentToken.type == TokenType::HYPHEN) {
            if (in_range) {
                throw std::runtime_error("Invalid range in group");
            }
            in_range = true;
            advance();
            continue;
        }
        
        if (m_currentToken.type == TokenType::CHAR) {
            if (in_range) {
                if (range_start == '\0') {
                    throw std::runtime_error("Invalid range in group");
                }
                group->addRange(range_start, m_currentToken.value);
                in_range = false;
                range_start = '\0';
            } else {
                group->addChar(m_currentToken.value);
                range_start = m_currentToken.value; // сохраняем для возможного диапазона
            }
            advance();
        } else {
            throw std::runtime_error("Invalid character in group");
        }
    }
    
    advance(); // consume ']'
    return group;
}