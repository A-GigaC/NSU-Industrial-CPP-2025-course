#pragma once

#include <memory>
#include "AST.h"

using namespace std;


namespace regex {

/**
 * @brief Класс для сопоставления строк с регулярным выражением
 */
class Matcher {
private:
    unique_ptr<ASTNode> m_pattern;
    
public:
    explicit Matcher(unique_ptr<ASTNode> pattern);
    
    /**
     * @brief Сопоставляет строку с регулярным выражением
     * @param str Строка для сопоставления
     * @return true если строка соответствует регулярному выражению, иначе false
     */
    bool match(const string& str) const;
};

} // namespace regex