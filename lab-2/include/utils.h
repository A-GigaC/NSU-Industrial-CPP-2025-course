#pragma once

#include <string>
#include <vector>

using namespace std;

namespace utils {
    /**
     * @brief Разделяет строку на подстроки по разделителю
     * @param str Исходная строка
     * @param delimiter Разделитель
     * @return Вектор подстрок
     */
    vector<string> split(const string& str, char delimiter);
    
    /**
     * @brief Проверяет, находится ли символ в диапазоне
     * @param c Проверяемый символ
     * @param start Начало диапазона
     * @param end Конец диапазона
     * @return true если символ в диапазоне, иначе false
     */
    bool isInRange(char c, char start, char end);
}