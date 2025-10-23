#include "regex/Matcher.h"

using namespace regex;
using namespace std;

Matcher::Matcher(unique_ptr<ASTNode> pattern) 
    : m_pattern(move(pattern)) {}

bool Matcher::match(const string& str) const {
    auto [matched, pos] = m_pattern->match(str, 0);
    return matched && pos == str.length();
}