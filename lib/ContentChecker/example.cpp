#include "my_library.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    // Проверка файла с использованием библиотеки
    int result = MyLibrary::checkFile(argc, argv);

    // Обработка результата
    if (result == 0)
    {
        std::cout << "Файл проверен успешно." << std::endl;
    }
    else
    {
        std::cerr << "Произошла ошибка при проверке файла." << std::endl;
    }

    return result;
}
