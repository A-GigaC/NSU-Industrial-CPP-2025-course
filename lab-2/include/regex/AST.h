#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_set>

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
    virtual std::pair<bool, size_t> match(const std::string& str, size_t pos) const = 0;
    
    /**
     * @brief Клонирует узел
     * @return Умный указатель на копию узла
     */
    virtual std::unique_ptr<ASTNode> clone() const = 0;
};

/**
 * @brief Узел для одиночного символа
 */
class CharNode : public ASTNode {
private:
    char m_char;
    
public:
    explicit CharNode(char c);
    std::pair<bool, size_t> match(const std::string& str, size_t pos) const override;
    std::unique_ptr<ASTNode> clone() const override;
};

/**
 * @brief Узел для любого символа (.)
 */
class AnyCharNode : public ASTNode {
public:
    std::pair<bool, size_t> match(const std::string& str, size_t pos) const override;
    std::unique_ptr<ASTNode> clone() const override;
};

/**
 * @brief Узел для группы символов ([abc])
 */
class GroupNode : public ASTNode {
private:
    std::unordered_set<char> m_chars;
    
public:
    void addChar(char c);
    void addRange(char from, char to);
    std::pair<bool, size_t> match(const std::string& str, size_t pos) const override;
    std::unique_ptr<ASTNode> clone() const override;
};

/**
 * @brief Узел для модификаторов (*, +, ?)
 */
class ModifierNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> m_child;
    char m_modifier;
    
public:
    ModifierNode(std::unique_ptr<ASTNode> child, char modifier);
    std::pair<bool, size_t> match(const std::string& str, size_t pos) const override;
    std::unique_ptr<ASTNode> clone() const override;
};

/**
 * @brief Узел для последовательности выражений
 */
class SequenceNode : public ASTNode {
private:
    std::vector<std::unique_ptr<ASTNode>> m_children;
    
public:
    void addNode(std::unique_ptr<ASTNode> node);
    std::pair<bool, size_t> match(const std::string& str, size_t pos) const override;
    std::unique_ptr<ASTNode> clone() const override;
};

} // namespace regex