#ifndef CONTENTCHECKER_HPP
#define CONTENTCHECKER_HPP

#include <string>
#include <utility>
#include <map>
#include <vector>

namespace contentChecker {

    // ������� ��� ������ ������ �� �������� ������
    auto& readstr(std::string& s);

    // ������� ��� ������ ����� � �������� ������� �����
    bool read(std::string& s);

    // ������� ��� ��������� ����������� ����� �� ������
    std::string get_right_number(std::string& line);

    // ������� ��� ��������, �������� �� ������ ������
    bool isnumber(std::string s);

    // ������� ��� ��������� �������� ����� ������
    std::string get_number_part(std::string s);

    // ������� ��� �������� �����
    std::string parse_name(std::string name);

    // ������� ��� �������� ������ � ����������� ���� (���, �����)
    bool parse(std::string line, std::pair<std::string, int>& res);

    // ������� ��� �������� �����
    bool block(std::string s);

    // �������� ������� ��� �������� �����
    int checkFile(int argc, char* argv[]);

} // namespace contentChecker

#endif // CONTENTCHECKER_HPP
