#include <gtest/gtest.h>
#include <memory>
#include "regex/Parser.h"
#include "regex/Matcher.h"

/**
 * @brief Тестовый класс для регулярных выражений
 */
class RegexTest : public ::testing::Test {
protected:
    void SetUp() override {}
    
    void TearDown() override {}
    
    /**
     * @brief Вспомогательная функция для тестирования сопоставления
     */
    void testMatch(const std::string& pattern, const std::string& input, bool expected) {
        try {
            regex::Parser parser(pattern);
            auto ast = parser.parse();
            regex::Matcher matcher(std::move(ast));
            
            bool result = matcher.match(input);
            EXPECT_EQ(result, expected) 
                << "Pattern: '" << pattern << "' with input: '" << input 
                << "' expected: " << expected << " but got: " << result;
        } catch (const std::exception& e) {
            FAIL() << "Exception for pattern '" << pattern << "' with input '" 
                   << input << "': " << e.what();
        }
    }
};

// Базовые тесты на сопоставление символов
TEST_F(RegexTest, BasicCharacterMatching) {
    testMatch("abc", "abc", true);
    testMatch("abc", "ab", false);
    testMatch("abc", "abcd", false);
    testMatch("hello", "hello", true);
    testMatch("hello", "world", false);
}

// Тесты для любого символа (.)
TEST_F(RegexTest, AnyCharacterMatching) {
    testMatch("a.c", "abc", true);
    testMatch("a.c", "axc", true);
    testMatch("a.c", "ac", false);
    testMatch("a.c", "abbc", false);
    testMatch("...", "abc", true);
    testMatch("...", "ab", false);
}

// Тесты для групп символов
TEST_F(RegexTest, CharacterGroups) {
    testMatch("[abc]", "a", true);
    testMatch("[abc]", "b", true);
    testMatch("[abc]", "c", true);
    testMatch("[abc]", "d", false);
    testMatch("[aeiou]", "a", true);
    testMatch("[aeiou]", "x", false);
}

// Тесты для диапазонов в группах
TEST_F(RegexTest, CharacterRanges) {
    testMatch("[a-c]", "a", true);
    testMatch("[a-c]", "b", true);
    testMatch("[a-c]", "c", true);
    testMatch("[a-c]", "d", false);
    testMatch("[0-9]", "5", true);
    testMatch("[0-9]", "a", false);
}

// Тесты для модификатора *
TEST_F(RegexTest, StarModifier) {
    testMatch("a*b", "b", true);
    testMatch("a*b", "ab", true);
    testMatch("a*b", "aab", true);
    testMatch("a*b", "aa", false);
    testMatch("a*b", "ac", false);
    testMatch(".*", "", true);
    testMatch(".*", "abc", true);
}

// Тесты для модификатора +
TEST_F(RegexTest, PlusModifier) {
    testMatch("a+b", "ab", true);
    testMatch("a+b", "aab", true);
    testMatch("a+b", "b", false);
    testMatch("a+b", "ac", false);
    testMatch(".+", "a", true);
    testMatch(".+", "", false);
}

// Тесты для модификатора ?
TEST_F(RegexTest, QuestionModifier) {
    testMatch("a?b", "b", true);
    testMatch("a?b", "ab", true);
    testMatch("a?b", "aab", false);
    testMatch("a?b", "ac", false);
    testMatch(".?", "", true);
    testMatch(".?", "a", true);
    testMatch(".?", "ab", false);
}

// Тесты комбинаций модификаторов
TEST_F(RegexTest, CombinedModifiers) {
    testMatch("a.*b", "ab", true);
    testMatch("a.*b", "axb", true);
    testMatch("a.*b", "axyzb", true);
    testMatch("a.*b", "a", false);
    testMatch("a.+b", "ab", true);
    testMatch("a.+b", "axb", true);
    testMatch("a.+b", "a", false);
}

// Тесты сложных регулярных выражений
TEST_F(RegexTest, AdvancedPatterns) {
    testMatch("[a-z]+[0-9]*", "hello", true);
    testMatch("[a-z]+[0-9]*", "hello123", true);
    testMatch("[a-z]+[0-9]*", "123", false);
}

// Тесты пограничных случаев
TEST_F(RegexTest, EdgeCases) {
    testMatch("", "", true);
    testMatch("", "a", false);
    testMatch("a", "", false);
    testMatch(".*", "", true);
    testMatch(".+", "", false);
    testMatch("a?", "", true);
}

// Тест на обработку ошибок
TEST_F(RegexTest, ErrorHandling) {
    // Незакрытая группа
    EXPECT_THROW({
        regex::Parser parser("[abc");
        auto ast = parser.parse();
    }, std::runtime_error);
}