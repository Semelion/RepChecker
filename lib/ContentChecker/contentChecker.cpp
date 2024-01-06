#define _CRT_SECURE_NO_WARNINGS
#include <sstream>
#include <algorithm>
#include <bitset>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <filesystem>

auto& readstr(std::string& s)
{
    auto& p = getline(std::cin, s);
    return p;
}

int line = 0;
bool read(std::string& s)
{
    if (readstr(s))
    {
        bool isn = 1;
        for (auto& i : s)
        {
            if (i < 0 || !isdigit(i))
            {
                isn = 0;
                break;
            }
        }
        if (isn && std::stoi(s) <= line + 2)
            line = std::stoi(s);
        if (isn)
            readstr(s);
        return 1;
    }
    return 0;
}

//char empty[4][1024];

namespace std
{
    string get_right_number(string& line)
    {
        reverse(line.begin(), line.end());
        stringstream tmp_ss;
        tmp_ss << line;
        string numval;
        tmp_ss >> numval;
        reverse(numval.begin(), numval.end());
        reverse(line.begin(), line.end());
        return numval;
    }

    bool isnumber(string s)
    {
        bool isn = 1;
        for (auto& i : s)
        {
            if (i < 0 || !isdigit(i))
            {
                isn = 0;
                break;
            }
        }
        return isn;
    }

    string get_number_part(string s)
    {
        string res;
        for (auto& i : s)
        {
            if (i == ' ' && res.empty())
                continue;
            if (i >= 0 && isdigit(i))
            {
                res += i;
            }
            else
            {
                break;
            }
        }
        return res;
    }

    string parse_name(string name)
    {
        int number = -1;
        if (name.substr(0, 22) == "Практическая работа № " || name.substr(0, 23) == "Практическое занятие № ")
            number = stoi(get_number_part(name.substr(22)));
        if (number != -1)
        {
            return "Практическая работа №" + to_string(number);
        }
        while (1 && !name.empty() && name.back() >= 0 && !isalpha(name.back()) && !isdigit(name.back()))
            name.pop_back();
        return name;
        //return name;
    }

    bool parse(string line, pair<string, int>& res)
    {
        string numval = get_right_number(line);
        if (!isnumber(numval))
            return 0;
        res = { parse_name(line.substr(0,line.size() - numval.size() - 1)),stoi(numval) };
        return 1;
    }

    bool block(string s)
    {
        stringstream ss;
        ss << s;
        string tmp;
        int words = 0;
        while (ss >> tmp) words++;
        return words <= 4 && words >= 1 && s.size() <= 100 && (s[0] < 0 || isupper(s[0]));
    }
}

int contentChecker()
{
    setlocale(LC_ALL, "Russian");
    if (__argc < 2 || __argc > 4)
    {
        std::cout << "Usage: parser file.txt [log.txt]\n";
        return 0;
    }
    FILE* s;
    if (freopen_s(&s, __argv[1], "r", stdin))
    {
        std::cout << "Error: cannot read file " << __argv[1];
        return 0;
    }
    if (__argc == 3)
    {
        std::cout << "Log redirected to " << __argv[2] << std::endl;
        freopen_s(&s, __argv[2], "w", stdout);
    }
    std::string l;
    while (read(l) && l.substr(0, 10) != "Оглавление" && l.substr(0, 10) != "Содержание")
    {
        //_CrtDbgBreak();
    }
    if (line == 0)
    {
        std::cout << "No line numbers found. Numbers check is disabled\n";
    }
    if (l.substr(0, 10) != "Оглавление" && l.substr(0, 10) != "Содержание")
    {
        std::cout << "Не найдено оглавление. Проверьте что в файле есть строка \"Оглавление\" или \"Содержание\"";
        return 0;
    }
    std::map<std::string, int> head;
    while (read(l))
    {
        std::pair<std::string, int> t;
        if (!std::parse(l, t))
            break;
        if (head.count(std::parse_name(l)))
            break;
        head.insert(t);
    }
    std::vector<std::pair<std::string, int>> lst2;
    do
    {
        lst2.emplace_back(std::parse_name(l), line);
    } while (read(l));
    for (auto& i : lst2)
    {
        if (!head.count(i.first))
        {
            //printf("Блок \"%s\" из файла не найден в оглавлении *\n", i.first.c_str());
        }
        else if (i.second != head[i.first])
        {
            std::cout << "Блок \"" << i.first << "\" в содержании указан с неверным номером страницы\n"
                "(Номер в оглавлении " << head[i.first] << " Номер в файле " << i.second << ")\n";
            head.erase(i.first);
        }
        else
        {
            head.erase(i.first);
        }

    }
    for (auto& i : head)
    {
        std::cout << "Блок \"" << i.first << "\" из оглавления не найден в файле\n";
    }
    std::cout << "OK" << std::endl;
    return 0;
}