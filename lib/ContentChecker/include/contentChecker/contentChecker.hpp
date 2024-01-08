#ifndef CONTENT_CHECKER_HPP
#define CONTENT_CHECKER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm>

class StringUtilities {
public:
    static std::string readstr(std::istream& input = std::cin);
    static bool isNumber(const std::string& s);
    static std::string getNumberPart(const std::string& s);
    static std::string parseName(std::string name);
};

class FileParser {
private:
    int line;
    std::map<std::string, int> head;
    std::vector<std::pair<std::string, int>> lst2;

public:
    FileParser();

    bool read(std::istream& input = std::cin);
    bool parse(const std::string& line, std::pair<std::string, int>& res);
    bool block(const std::string& s);
    void processFile(const std::string& fileName, const std::string& logFileName);
};

#endif // CONTENT_CHECKER_HPP
