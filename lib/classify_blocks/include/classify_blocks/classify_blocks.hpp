#ifndef CLASSIFY_HPP_22_12_23
#define CLASSIFY_HPP_22_12_23
#endif

#include "rectangles/rectangles.hpp"

#include <algorithm>
#include <vector>

/*!
  \defgroup clf_lib Библиотека для классификации контента.
  @{
*/

/// Содержит возможные метки для содержимого блока.
enum class Label {
  text, ///< обычный  текст документа.
  large_text, ///< текст меньшего размера, чем обычный (м. б. сноски, пометки).
  small_text, ///< текст большего размера, чем обычный (м. б. заголовки).
  horizontal_line, ///< горизонтальная линия.
  vertical_line, ///< вертикальная линия.
  graphic, ///< м.б. графики, схемы, таблицы.
  picture ///< изображения (отличается от graphic плотностью пикселей).
};


inline std::ostream& operator<<(std::ostream& ostrm, const Label& lbl) {
  switch (lbl) {
    case Label::text:
      ostrm << "text";
      break;
    case Label::large_text:
      ostrm << "large_text";
      break;
    case Label::small_text:
      ostrm << "small_text";
      break;
    case Label::horizontal_line:
      ostrm << "horizontal_line";
      break;
    case Label::vertical_line:
      ostrm << "vertical_line";
      break;
    case Label::graphic:
      ostrm << "graphic";
      break;
    case::Label::picture:
      ostrm << "picture";
    default:
      break;
  }
  return ostrm;
}

/*!
   \brief основной и единственный класс.
*/
class ClassifyRectangles {
  
  public:
    /*!
    * \param images вектор с исходными исзображениями.
    * \param rectangles содержит координаты зон с содержимым, которое будем классифицировать.
    */
    ClassifyRectangles(const std::vector<cv::Mat>& images, const CutRectangles& rectangles);
    ~ClassifyRectangles();
    ClassifyRectangles(const ClassifyRectangles& other) = delete;
    ClassifyRectangles& operator=(const ClassifyRectangles& other) = delete;
    ClassifyRectangles(ClassifyRectangles&& other) = default;
    /*!
      \brief метод для вывода страницу с метками типа контента.

      \param i_page номер страницы.
    */
    void PrintPageWithClassifiedRect(ptrdiff_t i_page) const;
    /*!
      \brief метод для получения типа содержимого, ограниченного конкретным прямоугольником.

      \param i_page номер страницы.
      \param i_rect номер прямоугольника на странице (нулевой прямоугольник - самый верхний).
    
      \return тип контента.
    */
    Label at(int i_page, int i_rect) const;

  private:
    const double c1 = 0.7; 
    const double c2 = 1.2; 
    const double c3 = 0.95; 
    const double c4 = 1.05; 
    const double c5 = 0.2;
    const double ch1 = 1.2;
    const double ch2 = 3;
    const double ch3 = 0.2;
    const double cv1 = 1.2;
    const double cv2 = 2.6;
    const double cr = 5;

  private:
    const CutRectangles* rectangles_ptr = nullptr;
    std::vector<std::vector<Label>> rectangles_types;
    /*!
      \brief метод для нахождения количества черных пикселей в области.
    */
    int NumberOfBlackPixels(const cv::Mat& img_area);
    /*!
      \brief метод для нахождения количества таких черных пикселей, что перед каждым стоит белый пиксель.
    */
    int HorizWhiteToBlackTransitions(const cv::Mat& img_area);
    /*!
      \brief метод для нахождения количества таких черных пикселей, что сверху над каждым стоит белый пиксель.
    */
    int VertWhiteToBlackTransitions(const cv::Mat& img_area);
    /*!
      \brief метод для нахождения количества столбцов, содержащих хотя бы один черный пиксель.
    */
    int ColsWithBlackPixels(const cv::Mat& img_area);
    std::vector<cv::Mat> pages;

  private:
    static std::vector<cv::Scalar> color_for_label;
    static std::string LabelToStr(Label lbl);
};  

/*!
  @}
*/