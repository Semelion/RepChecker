#ifndef CLASSIFY_HPP_22_12_23
#define CLASSIFY_HPP_22_12_23
#endif

#include "rectangles/rectangles.hpp"

#include <vector>
#include <algorithm>

enum class Label {
  text,
  large_text, // titles, headings
  small_text, // footnotes, remarks 
  horizontal_line,
  vertical_line,
  graphic,
  picture
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
class ClassifyRectangles {
  
  public:
    ClassifyRectangles(const std::vector<cv::Mat>& images, const CutRectangles& rectangles);
    ~ClassifyRectangles() = default;
    // ClassifyRectangles(const ClassifyRectangles& other) = default;
    // ClassifyRectangles(ClassifyRectangles&& other) = default;
    // ClassifyRectangles& operator=(ClassifyRectangles&& other) = default;
    // ClassifyRectangles& operator=(const ClassifyRectangles& other) = default;

  public:
    void PrintPageWithClassifiedRect(ptrdiff_t i_page) const;
    Label at(int i_page, int i_rect) const;

  private:
    const double c1 = 0.8;
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
    const CutRectangles* rectangles_ptr;
    std::vector<std::vector<Label>> rectangles_types;
    int NumberOfBlackPixels(const cv::Mat& img_area);
    int HorizWhiteToBlackTransitions(const cv::Mat& img_area);
    int VertWhiteToBlackTransitions(const cv::Mat& img_area);
    int ColsWithBlackPixels(const cv::Mat& img_area);
    std::vector<cv::Mat> pages;

  private:
    static std::vector<cv::Scalar> color_for_label;
};  