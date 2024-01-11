#pragma once
#ifndef REPCHECK_CUT_RECTANGLES_HPP
#define REPCHECK_CUT_RECTANGLES_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cstddef>

/**
 * @brief Класс, который разделяет документ на последовательные блоки
 */
class CutRectangles{
public:
    /**
     * @brief Construct a new Cut Rectangles object
     *
     * @param images вектор изображений
     */
    CutRectangles(const std::vector<cv::Mat>& images);
    CutRectangles(cv::Mat image);
    ~CutRectangles();
    /**
     * @brief Get the rectangles object
     *
     * @return std::vector<std::vector<cv::Rect> > вектор векторов прямоугольников для каждой страницы
     */
    std::vector<std::vector<cv::Rect> > get_rectangles() noexcept; // returns rectangles from all pages
    /**
     * @brief Возвращает прямоугольники по индексу страницы
     *
     * @param ind индекс страницы
     * @return const std::vector<cv::Rect>& вектор прямоугольников для указанной страницы
     */
    const std::vector<cv::Rect>& operator[](const ptrdiff_t ind) const; // returns rectangles by page index
    /**
     * @brief Возвращает кол-во страниц
     *
     * @return ptrdiff_t
     */
    ptrdiff_t ssize() const noexcept;
    void imshow_with_rectangles(int page);
private:
    cv::Mat reducePageOy(const cv::Mat& image) noexcept;
    cv::Mat reducePageOx(const cv::Mat& image) noexcept;
    std::vector<cv::Rect> pre_count_blocks(cv::Mat projection, int missingDimension, int projection_type, int page=-1); // projection: 1 - oy, 0 - ox

private:
    cv::Scalar DEBUG_COLOR = cv::Scalar(0, 255, 0); ///< Цвет для отладки (Зеленый)
    int RLSA_VALUE = 15; ///< Значение сглаживания пикселей для 300 DPI
    std::vector<cv::Mat> pages_;
    std::vector<std::vector<cv::Rect> > rectangles_in_pages;
};

#endif // REPCHECK_CUT_RECTANGLES_HPP
