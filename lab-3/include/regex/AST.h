#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

namespace regex {

/**
 * @brief Базовый класс для всех узлов AST регулярного выражения
 */
class ASTNode {
public:
    virtual ~ASTNode() = default;
    
    /**
     * @brief Сопоставляет узел со строкой
     * @param str Строка для сопоставления
     * @param pos Текущая позиция в строке
     * @return Пару (успех, новая позиция)
     */
    virtual pair<bool, size_t> match(const string& str, size_t pos) const = 0;
    
    /**
     * @brief Клонирует узел
     * @return Умный указатель на копию узла
     */
    virtual unique_ptr<ASTNode> clone() const = 0;
};

/**
 * @brief Нода одиночного символа
 */
class CharNode : public ASTNode {
private:
    char m_char;
    
public:
    explicit CharNode(char c);
    pair<bool, size_t> match(const string& str, size_t pos) const override;
    unique_ptr<ASTNode> clone() const override;
};

/**
 * @brief Нода любого символа (.)
 */
class AnyCharNode : public ASTNode {
public:
    pair<bool, size_t> match(const string& str, size_t pos) const override;
    unique_ptr<ASTNode> clone() const override;
};

/**
 * @brief Нода группы символов ([abc])
 */
class GroupNode : public ASTNode {
private:
    unordered_set<char> m_chars;
    
public:
    void addChar(char c);
    void addRange(char from, char to);
    pair<bool, size_t> match(const string& str, size_t pos) const override;
    unique_ptr<ASTNode> clone() const override;
};

/**
 * @brief Нода модификаторов (*, +, ?)
 */
class ModifierNode : public ASTNode {
private:
    unique_ptr<ASTNode> m_child;
    char m_modifier;
    
public:
    ModifierNode(unique_ptr<ASTNode> child, char modifier);
    pair<bool, size_t> match(const string& str, size_t pos) const override;
    unique_ptr<ASTNode> clone() const override;
};

/**
 * @brief Нода последовательности выражений
 */
class SequenceNode : public ASTNode {
private:
    vector<unique_ptr<ASTNode>> m_children;
    
public:
    void addNode(unique_ptr<ASTNode> node);
    pair<bool, size_t> match(const string& str, size_t pos) const override;
    unique_ptr<ASTNode> clone() const override;
};

} // namespace regex