#include "regex/Matcher.h"

using namespace regex;

Matcher::Matcher(std::unique_ptr<ASTNode> pattern) 
    : m_pattern(std::move(pattern)) {}

bool Matcher::match(const std::string& str) const {
    auto [matched, pos] = m_pattern->match(str, 0);
    return matched && pos == str.length();
}