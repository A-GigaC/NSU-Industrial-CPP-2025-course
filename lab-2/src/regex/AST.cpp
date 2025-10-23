#include "regex/AST.h"
#include <stdexcept>

using namespace regex;
using namespace std;

// CharNode implementation
CharNode::CharNode(char c) : m_char(c) {}

pair<bool, size_t> CharNode::match(const string& str, size_t pos) const {
    if (pos < str.length() && str[pos] == m_char) {
        return {true, pos + 1};
    }
    return {false, pos};
}

unique_ptr<ASTNode> CharNode::clone() const {
    return make_unique<CharNode>(m_char);
}

// AnyCharNode implementation
pair<bool, size_t> AnyCharNode::match(const string& str, size_t pos) const {
    if (pos < str.length()) {
        return {true, pos + 1};
    }
    return {false, pos};
}

unique_ptr<ASTNode> AnyCharNode::clone() const {
    return make_unique<AnyCharNode>();
}

// GroupNode implementation
void GroupNode::addChar(char c) {
    m_chars.insert(c);
}

void GroupNode::addRange(char from, char to) {
    for (char c = from; c <= to; ++c) {
        m_chars.insert(c);
    }
}

pair<bool, size_t> GroupNode::match(const string& str, size_t pos) const {
    if (pos < str.length() && m_chars.find(str[pos]) != m_chars.end()) {
        return {true, pos + 1};
    }
    return {false, pos};
}

unique_ptr<ASTNode> GroupNode::clone() const {
    auto node = make_unique<GroupNode>();
    for (char c : m_chars) {
        node->addChar(c);
    }
    return node;
}

// ModifierNode implementation
ModifierNode::ModifierNode(unique_ptr<ASTNode> child, char modifier) 
    : m_child(move(child)), m_modifier(modifier) {}

pair<bool, size_t> ModifierNode::match(const string& str, size_t pos) const {
    switch (m_modifier) {
        case '*': { // 0 или более раз (жадный)
            size_t max_pos = pos;
            auto current_pos = pos;
            
            // Пытаемся найти максимальное совпадение
            while (true) {
                auto [matched, new_pos] = m_child->match(str, current_pos);
                if (!matched || new_pos == current_pos) {
                    break;
                }
                current_pos = new_pos;
                max_pos = current_pos;
            }
            
            return {true, max_pos};
        }
        
        case '+': { // 1 или более раз (жадный)
            auto [matched, new_pos] = m_child->match(str, pos);
            if (!matched) {
                return {false, pos};
            }
            
            size_t max_pos = new_pos;
            auto current_pos = new_pos;
            
            // Пытаемся найти максимальное совпадение
            while (true) {
                auto [matched_inner, new_pos_inner] = m_child->match(str, current_pos);
                if (!matched_inner || new_pos_inner == current_pos) {
                    break;
                }
                current_pos = new_pos_inner;
                max_pos = current_pos;
            }
            
            return {true, max_pos};
        }
        
        case '?': { // 0 или 1 раз (ленивый)
            // Сначала пробуем 0 раз
            auto [matched, new_pos] = m_child->match(str, pos);
            if (matched) {
                // Проверяем, можем ли мы сопоставить остаток строки с текущей позицией
                return {true, new_pos};
            }
            // Если 1 раз не удалось, возвращаем 0 раз
            return {true, pos};
        }
        
        default:
            throw runtime_error("Unknown modifier");
    }
}

unique_ptr<ASTNode> ModifierNode::clone() const {
    return make_unique<ModifierNode>(m_child->clone(), m_modifier);
}

// SequenceNode implementation
void SequenceNode::addNode(unique_ptr<ASTNode> node) {
    m_children.push_back(move(node));
}

pair<bool, size_t> SequenceNode::match(const string& str, size_t pos) const {
    size_t current_pos = pos;
    
    for (const auto& child : m_children) {
        auto [matched, new_pos] = child->match(str, current_pos);
        if (!matched) {
            return {false, pos};
        }
        current_pos = new_pos;
    }
    
    return {true, current_pos};
}

unique_ptr<ASTNode> SequenceNode::clone() const {
    auto node = make_unique<SequenceNode>();
    for (const auto& child : m_children) {
        node->addNode(child->clone());
    }
    return node;
}