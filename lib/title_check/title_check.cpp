#include <title_check/title_check.hpp>

title_check::title_check(const std::vector<cv::Rect>& text_boxes,
  const int& title_rows, const int& title_cols,const int& dpi, const int& admission){
    for(auto& i: text_boxes){
      #if 1
  			std::cout << "C: " << check_centering_text(i.x, i.x + i.width, title_cols, 300, 100)
  			<< " R: " << check_centering_right_text(i.x, i.x + i.width, title_cols) << '\n';
      #endif
			if (check_centering_text(i.x, i.x + i.width, title_cols))
				centering_blocks.push_back('c');
			else {
				if (check_centering_right_text(i.x, i.x + i.width, title_cols))
					centering_blocks.push_back('r');
				else
					centering_blocks.push_back('?');
			}
      /*if(check_centering_text(i.x, i.x + i.width, title_cols))
      	centering_blocks.push_back(1);
      else
      	centering_blocks.push_back(-1);*/
  	}

}

std::string title_check::get_result(){
  for(auto& i: centering_blocks)
		std::cout << i << '\n';
	std::cout << "_______________________________" << '\n';
	std::cout << std::count(centering_blocks.begin(), centering_blocks.end(), 'c') << '\n';
	if (centering_blocks[centering_blocks.size() - 2] == 'r' &&
		centering_blocks[centering_blocks.size() - 3] == 'r' &&
		std::count(centering_blocks.begin(), centering_blocks.end(), 'c') == centering_blocks.size() - 2)
		return "good title";
	else
		return "wrong title, try to check indents, alignments or line spacing";
}

bool check_centering_text(const int& x_left, const int& x_right, const int& sheet_width,
	const int& dpi, const int& admission ){
	if( std::abs((x_left - (dpi/25.4)*30) - (sheet_width - ((dpi/25.4)*10) - x_right) ) < admission)
		return true;
	else
		return false;
}

bool check_centering_right_text(const int& x_left, const int& x_right, const int& sheet_width,
	const int& dpi, const int& admission){
		if(std::abs(sheet_width - ((dpi/25.4)*10) - x_right) < admission)
			return true;
		else
			return false;
}
