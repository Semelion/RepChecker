#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm>

// Класс для работы с строками
class StringUtilities {
public:
    // Статический метод для считывания строки из потока
    static std::string readstr(std::istream& input = std::cin) {
        std::string s;
        std::getline(input, s);
        return s;
    }

    // Статический метод для проверки, является ли строка числом
    static bool isNumber(const std::string& s) {
        return std::all_of(s.begin(), s.end(), [](char c) { return std::isdigit(c) || c < 0; });
    }

    // Статический метод для извлечения числовой части строки
    static std::string getNumberPart(const std::string& s) {
        std::string res;
        for (auto& i : s) {
            if (i == ' ' && res.empty()) continue;
            if (i >= 0 && std::isdigit(i)) {
                res += i;
            }
            else {
                break;
            }
        }
        return res;
    }

    // Статический метод для парсинга имени, извлечение номера, если присутствует
    static std::string parseName(std::string name) {
        int number = -1;
        if (name.substr(0, 22) == "Практическая работа № " || name.substr(0, 23) == "Практическое занятие № ") {
            number = std::stoi(getNumberPart(name.substr(22)));
        }
        if (number != -1) {
            return "Практическая работа №" + std::to_string(number);
        }
        while (!name.empty() && name.back() >= 0 && !std::isalpha(name.back()) && !std::isdigit(name.back())) {
            name.pop_back();
        }
        return name;
    }
};

// Класс для парсинга файла и проверки содержимого
class FileParser {
private:
    int line;
    std::map<std::string, int> head;
    std::vector<std::pair<std::string, int>> lst2;

public:
    // Конструктор класса
    FileParser() : line(0) {}

    // Метод для считывания строки из потока
    bool read(std::istream& input = std::cin) {
        std::string s;
        std::getline(input, s);
        if (!s.empty()) {
            bool isn = true;
            for (auto& i : s) {
                if (i < 0 || !std::isdigit(i)) {
                    isn = false;
                    break;
                }
            }
            if (isn && std::stoi(s) <= line + 2) {
                line = std::stoi(s);
            }
            if (isn) {
                std::getline(input, s);
            }
            return true;
        }
        return false;
    }

    // Метод для парсинга строки и извлечения информации
    bool parse(const std::string& line, std::pair<std::string, int>& res) {
        std::string numval = StringUtilities::getNumberPart(line);
        if (!StringUtilities::isNumber(numval)) {
            return false;
        }
        res = { StringUtilities::parseName(line.substr(0, line.size() - numval.size() - 1)), std::stoi(numval) };
        return true;
    }

    // Метод для проверки блока текста
    bool block(const std::string& s) {
        std::stringstream ss(s);
        std::string tmp;
        int words = 0;
        while (ss >> tmp) {
            words++;
        }
        return words <= 4 && words >= 1 && s.size() <= 100 && (s[0] < 0 || std::isupper(s[0]));
    }

    // Метод для обработки содержимого файла
    void processFile(const std::string& fileName, const std::string& logFileName) {
        std::ifstream fileStream(fileName);
        std::ofstream logStream;

        if (!fileStream.is_open()) {
            std::cout << "Error: cannot read file " << fileName << std::endl;
            return;
        }

        if (!logFileName.empty()) {
            logStream.open(logFileName);
            if (!logStream.is_open()) {
                std::cout << "Error: cannot open log file " << logFileName << std::endl;
                return;
            }
            std::cout << "Log redirected to " << logFileName << std::endl;
        }
        std::string line;
        while (read(fileStream) && line.substr(0, 10) != "Оглавление" && line.substr(0, 10) != "Содержание") {
            // Ничего не делать, пропустить строки до оглавления
        }

        if (line == "0") {
            std::cout << "No line numbers found. Numbers check is disabled\n";
        }

        if (line.substr(0, 10) != "Оглавление" && line.substr(0, 10) != "Содержание") {
            std::cout << "Не найдено оглавление. Проверьте, что в файле есть строка \"Оглавление\" или \"Содержание\"";
            return;
        }

        while (read(fileStream)) {
            std::pair<std::string, int> t;
            if (!parse(line, t)) {
                break;
            }
            if (head.count(StringUtilities::parseName(line))) {
                break;
            }
            head.insert(t);
        }

        do {
            lst2.emplace_back(StringUtilities::parseName(line), std::stoi(line));
        } while (read(fileStream));

        for (auto& i : lst2) {
            if (!head.count(i.first)) {
                //printf("Блок \"%s\" из файла не найден в оглавлении *\n", i.first.c_str());
            }
            else if (i.second != head[i.first]) {
                std::cout << "Блок \"" << i.first << "\" в содержании указан с неверным номером страницы\n"
                    "(Номер в оглавлении " << head[i.first] << " Номер в файле " << i.second << ")\n";
                head.erase(i.first);
            }
            else {
                head.erase(i.first);
            }
        }

        for (auto& i : head) {
            std::cout << "Блок \"" << i.first << "\" из оглавления не найден в файле\n";
        }

        std::cout << "OK" << std::endl;
    }
};

// Точка входа в программу
int main(int argc, char* argv[]) {
    FileParser fileParser;

    if (argc < 2 || argc > 4) {
        std::cout << "Usage: parser file.txt [log.txt]\n";
        return 0;
    }

    std::string logFileName = (argc == 3) ? argv[2] : "";

    fileParser.processFile(argv[1], logFileName);

    return 0;
}
