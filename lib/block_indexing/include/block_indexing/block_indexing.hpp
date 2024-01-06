#pragma once
#ifndef BLOCK_INDEXING_HPP
#define BLOCK_INDEXING_HPP

#include <iostream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

#include <opencv2/imgcodecs.hpp>
#include <nlohmann/json.hpp>

#include <pdf2img/pdf2img.h>
#include <rectangles/rectangles.hpp>
#include <text_recognition/text_recognition.hpp>

/**
  * @brief Класс для разбиения документа на основные блоки (титульный лист, содержание, основная часть, список литературы, дополнения)
  */
class Block_indexing{
public:
  /**
    * @brief Разбиение документа на блоки и запись результата в JSON
    * @param doc_imgs массив матриц со страницами
    * doc_imgs text_boxes массив прямоугольников с блоками текста
    */
  Block_indexing(pdf2img& doc_imgs, CutRectangles& text_boxes);

  /**
  	* @brief Получение разметки
  	* @return JSON с информацией наличия блока, первой и последней страницами
  	*/
  nlohmann::json get_indexing();
  /**
  	* @brief Получение списка ошибок
  	* @return JSON с информацией об ошибкав в документе
  	*/
  nlohmann::json get_errors();

private:
  nlohmann::json indexes = nlohmann::json::parse(R"(
  {
    "have_title_page" : false,
    "content_list" : {
      "in_dock" : false,
      "start" : -1,
      "end" : -1
    },
    "main_part" : {
      "in_dock" : false,
      "start" : -1,
      "end" : -1
    },
    "sources" : {
      "in_dock" : false,
      "start" : -1,
      "end" : -1
    },
    "extra_part" : {
      "in_dock" : false,
      "start" : -1,
      "end" : -1
    }
  }
  )");
  nlohmann::json errors_ = nlohmann::json::parse(R"({})");
};

#endif // REPCHECK_CUT_RECTANGLES_HPP
