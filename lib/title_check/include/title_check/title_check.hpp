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
  std::vector<int> centering_blocks;
  // const std::vector<cv::Rect>& text_boxes;
  // const int& title_rows;
  // const int& title_cols;
  // const int& dpi;
  // const int& admission;
};

bool check_centering_text(const int& x_left, const int& x_right, const int& sheet_width,
	const int& dpi = 300, const int& admission = 100){
	//dpi/25.4 = 1mm
	//left 30 mm rigt 10 mm
	#if 0
		std::cout << "________________________________________" << '\n';
		std::cout << "x_left: " << x_left <<'\n';
		std::cout << "x_right: " << x_right <<'\n';
		std::cout << "sheet_width: " << sheet_width <<'\n';
		std::cout << "(x_left - (dpi/25.4)*30): " << (x_left - (dpi/25.4)*30) << '\n';
		std::cout << "(sheet_width - ((dpi/25.4)*10) - x_right): " << (sheet_width - ((dpi/25.4)*10) - x_right) << '\n';
	#endif

	if(std::abs((x_left - (dpi/25.4)*30) - (sheet_width - ((dpi/25.4)*10) - x_right)) < admission)
		return true;
	else
		return false;
}

bool check_centering_right_text(const int& x_left, const int& x_right, const int& sheet_width,
	const int& dpi = 300, const int& admission = 10){
		//std::abs((x_left - (dpi/25.4)*30) - (sheet_width - ((dpi/25.4)*10) - x_right))
		if(std::abs(sheet_width - ((dpi/25.4)*10) - x_right) < admission)
			return true;
		else
			return false;
}
#endif
