#include "my_library.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    // �������� ����� � �������������� ����������
    int result = MyLibrary::checkFile(argc, argv);

    // ��������� ����������
    if (result == 0)
    {
        std::cout << "���� �������� �������." << std::endl;
    }
    else
    {
        std::cerr << "��������� ������ ��� �������� �����." << std::endl;
    }

    return result;
}
