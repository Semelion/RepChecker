#pragma once
#ifndef REPCHECK_INTERVALES_HPP
#define REPCHECK_INTERVALES_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <rectangles/rectangles.hpp>
#include <classify_blocks/classify_blocks.hpp>
#include <vector>
#include <queue>
#include <cstddef>
#include <map>

/**
 * @brief Класс, который реализует нахождение медианного значения для потока чисел
 * Структура реализована на двух приоритетных очередях
 */
class MedinasFromRunningData{
public:
    ~MedinasFromRunningData() = default;
    
    /**
     * @brief Добавление значения в очереди.
     * 
     * @param num число, которое нужно добавить
     */
    void push(int num) noexcept{
        maxHeap_.push(num);
        minHeap_.push(maxHeap_.top());
        maxHeap_.pop();
        if (maxHeap_.size() < minHeap_.size()) {
            maxHeap_.push(minHeap_.top());
            minHeap_.pop();
      }
    }

    /**
     * @brief Get the Median object
     * 
     * @return int 
     */
    int getMedian(){
        if (maxHeap_.size() == 0){
            return -1;
        }
        return maxHeap_.top();
    }

    /**
     * @brief Очищает данные
     * 
     */
    void clear() noexcept{
        while (maxHeap_.size() != 0){
            maxHeap_.pop();
        }
        while (minHeap_.size() != 0){
            minHeap_.pop();
        }
    }

private:
    std::priority_queue<int> maxHeap_;
    std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap_;
};

/**
 * @brief Класс, который проверяет междустрочный интервал.
 * 
 */
class Intervales{
public:
    /**
     * @brief Construct a new Intervales object
     * 
     * @param pages вектор изображений
     */
    Intervales(std::vector<cv::Mat> pages);
    /**
     * @brief Возвращает медианный междустрочный интервал для указанной страницы
     * 
     * @param page номер страницы
     * @return double значение междустрочного интервала
     */
    double get_current_page_interval(int page);
    /**
     * @brief Возвращает среднее значение междустрочного интервала
     * 
     * @return double значение междустрочного интервала
     */
    double get_avg_interval();
    /**
     * @brief Проверяет междустрочный интервал по алгоритму: медианное значение * TO_PT(перевод в пункты) / 1.5 / 1.18 (константы для шрифта). 
     * Можно улучшить проверку, передавая размер шрифта.
     * @return true если междустрочный интервал принадлежит шрифту 14 илил 12
     * @return false любое другое значение
     */
    bool check_intervale();
private:
    /**
     * @brief Возвращает коробочки (для каждой буквы - коробочка)
     * 
     * @param line_in_rectangle Вырезанная строка с текстом, который нужно разбить на буквы
     * @return std::vector<cv::Rect> прямоугольники - коробочка для каждого символа.
     */
    std::vector<cv::Rect> getIntervales(cv::Mat line_in_rectangle);
private:
    std::vector<cv::Mat> pages_;
    std::vector<MedinasFromRunningData> page_medians_;
    int START_PAGE = 1; ///< Страница, с которой начинать проверять междустрочный интервал.
    long long sum_intervales_ = 0;
    int cnt_intervales_ = 0;
    const int DPI = 300; ///< DPI изображения
    double TO_PT = 72.0 / DPI;
};
#endif // REPCHECK_INTERVALES_HPP