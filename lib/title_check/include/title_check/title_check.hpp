#ifndef title_check_LIBRARY_H
#define title_check_LIBRARY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class title_check{
	public:
    explicit title_check(const std::vector<cv::Rect>& text_boxes,
      const int& title_rows, const int& title_cols,const int& dpi = 300, const int& admission = 100);
    std::string get_result();
private:
  //std::vector<int> centering_blocks;
	std::vector<char> centering_blocks;
  // const std::vector<cv::Rect>& text_boxes;
  // const int& title_rows;
  // const int& title_cols;
  // const int& dpi;
  // const int& admission;
};

bool check_centering_text(const int& x_left, const int& x_right, const int& sheet_width,
	const int& dpi = 300, const int& admission = 100);

bool check_centering_right_text(const int& x_left, const int& x_right, const int& sheet_width,
	const int& dpi = 300, const int& admission = 10);


#endif
