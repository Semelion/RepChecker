#include <title_check/title_check.hpp>

title_check::title_check(const std::vector<cv::Rect>& text_boxes,
  const int& title_rows, const int& title_cols,const int& dpi, const int& admission){
    for(auto& i: text_boxes){
      #if 1
  			std::cout << "C: " << check_centering_text(i.x, i.x + i.width, title_cols, 300, 100)
  			<< " R: " << check_centering_right_text(i.x, i.x + i.width, title_cols) << '\n';
      #endif
      if(check_centering_text(i.x, i.x + i.width, title_cols))
      	centering_blocks.push_back(1);
      else
      	centering_blocks.push_back(-1);
  	}

}

std::string title_check::get_result(){
  for(auto& i: centering_blocks)
		std::cout << i << '\n';
	std::cout << "_______________________________" << '\n';
	std::cout << std::count(centering_blocks.begin(), centering_blocks.end(), -1) << '\n';
	if(centering_blocks[0] == 1 && 1 == centering_blocks[1] &&
		std::count(centering_blocks.begin(), centering_blocks.end(), -1) >= 4 &&
		centering_blocks[centering_blocks.size() - 1] == 1 && centering_blocks[centering_blocks.size() - 2] == 1){
      return "good title";
			//std::cout << "good title" << '\n';
	}else{
      return "wrong title";
		  //std::cout << "wrong title" << '\n';
	}
}
