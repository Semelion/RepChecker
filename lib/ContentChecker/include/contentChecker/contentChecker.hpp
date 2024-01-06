#ifndef CONTENTCHECKER_HPP
#define CONTENTCHECKER_HPP

#include <string>
#include <utility>
#include <map>
#include <vector>

namespace contentChecker {

    // Функция для чтения строки из входного потока
    auto& readstr(std::string& s);

    // Функция для чтения строк и проверки номеров строк
    bool read(std::string& s);

    // Функция для получения правильного числа из строки
    std::string get_right_number(std::string& line);

    // Функция для проверки, является ли строка числом
    bool isnumber(std::string s);

    // Функция для получения числовой части строки
    std::string get_number_part(std::string s);

    // Функция для парсинга имени
    std::string parse_name(std::string name);

    // Функция для парсинга строки и возвращения пары (имя, номер)
    bool parse(std::string line, std::pair<std::string, int>& res);

    // Функция для проверки блока
    bool block(std::string s);

    // Основная функция для проверки файла
    int checkFile(int argc, char* argv[]);

} // namespace contentChecker

#endif // CONTENTCHECKER_HPP
