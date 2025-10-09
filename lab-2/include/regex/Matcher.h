#pragma once

#include <memory>
#include "AST.h"

namespace regex {

/**
 * @brief Класс для сопоставления строк с регулярным выражением
 */
class Matcher {
private:
    std::unique_ptr<ASTNode> m_pattern;
    
public:
    explicit Matcher(std::unique_ptr<ASTNode> pattern);
    
    /**
     * @brief Сопоставляет строку с регулярным выражением
     * @param str Строка для сопоставления
     * @return true если строка соответствует регулярному выражению, иначе false
     */
    bool match(const std::string& str) const;
};

} // namespace regex