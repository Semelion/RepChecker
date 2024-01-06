#ifndef pdf2img_LIBRARY_H
#define pdf2img_LIBRARY_H

//#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-page-renderer.h>
#include <poppler-image.h>


/**
* @brief Класс для создания массива матриц отрендеренных страниц из PDF
*/
class pdf2img{
	public:
		/**
		* @brief Рендер страниц и сохранение матриц в массив
		* @param mypdf объект PDF библиотеки poppler
		* @param DPI количество точек на дюйм
		*/
	  explicit pdf2img(const poppler::document* mypdf, int DPI);


		/**
		* @brief Оператор доступа к элементам массива через []
		* @param i индекс странницы/матрицы
		* @return Матрицу cv::Mat
		*/
	  cv::Mat& operator[] (const std::ptrdiff_t i);

		/**
		* @brief Получение длины массива (количество странниц в документе)
		* @return Число странниц
		*/
		ptrdiff_t get_size();
private:
  ptrdiff_t capacity_ = 0;
	cv::Mat* data_ = nullptr;
};
#endif
