#ifndef title_check_LIBRARY_H
#define title_check_LIBRARY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

/**
* @brief Класс для проверки титульника по ГОСТу
*/
class title_check {
public:
	explicit title_check(const std::vector<cv::Rect>& text_boxes,
		const int& title_rows, const int& title_cols, const int& admission, const int& dpi = 300);
	/**
	* @brief Проверка титульника на соответствие ГОСТу
	* @return Выравнивание каждого блока
	*/
	std::string get_result();
private:
	std::string centering_blocks = "";

public:
	/**
		* @brief Проверка блока на выравнивание по середине
		* @param x_left абсцисса левого края блока
		* @param x_right абсцисса правого края блока
		* @param sheet_width высота блока
		* @param admission погрешность
		* @param dpi разрешение
		* @return true или false
		*/
	bool check_centering_text(const int& x_left, const int& x_right, const int& sheet_width,
		const int& admission, const int& dpi = 300);

	/**
		* @brief Проверка блока на выравнивание по правому краю
		* @return численный ответ
		*/
	bool check_centering_right_text(const int& x_left, const int& x_right, const int& sheet_width,
		const int& admission, const int& dpi = 300);

	/**
		* @brief Проверка блока на выравнивание по левому краю
		* @return численный ответ
		*/
	bool check_centering_left_text(const int& x_left, const int& x_right, const int& sheet_width,
		const int& admission, const int& dpi = 300);

};
#endif
