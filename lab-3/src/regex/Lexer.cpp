#include "regex/Lexer.h"

using namespace regex;
using namespace std;

Token::Token(TokenType t, char v) : type(t), value(v) {}

Lexer::Lexer(const string& input) 
    : m_input(input), m_position(0) {}

Token Lexer::nextToken() {
    if (m_position >= m_input.length()) {
        return Token(TokenType::END);
    }
    
    char current = m_input[m_position++];
    
    switch (current) {
        case '.': return Token(TokenType::DOT);
        case '[': return Token(TokenType::GROUP_OPEN);
        case ']': return Token(TokenType::GROUP_CLOSE);
        case '*': return Token(TokenType::STAR);
        case '+': return Token(TokenType::PLUS);
        case '?': return Token(TokenType::QUESTION);
        case '-': return Token(TokenType::HYPHEN);
        default:  return Token(TokenType::CHAR, current);
    }
}

size_t Lexer::getPosition() const {
    return m_position;
}