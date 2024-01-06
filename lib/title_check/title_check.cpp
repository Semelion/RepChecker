#include <title_check/title_check.hpp>

title_check::title_check(const std::vector<cv::Rect>& text_boxes,
	const int& title_rows, const int& title_cols, const int& admission, const int& dpi) {

	for (auto& i : text_boxes) {
#if 1
		// std::cout << "C: " << check_centering_text(i.x, i.x + i.width, title_cols, 300, 100)
		// << " R: " << check_centering_right_text(i.x, i.x + i.width, title_cols) << '\n';
#endif
		if (check_centering_text(i.x, i.x + i.width, title_cols, admission))
			centering_blocks.append("c");
		else {
			if (check_centering_right_text(i.x, i.x + i.width, title_cols, admission))
				centering_blocks.append("r");
			else {
				if (check_centering_left_text(i.x, i.x + i.width, title_cols, admission))
					centering_blocks.append("l");
				else
					centering_blocks.append("?");
			}
		};
	}
}

std::string title_check::get_result() {
	bool flag = true;
	std::string end = "";
	end = centering_blocks.substr(centering_blocks.size() - 4, 4);
	if (end != "rrcc" && end != "crrc" && end != "crcc" && end != "ccrc") {
		flag = false;
	}
	else {
		std::string begin = "";
		begin = centering_blocks.substr(0, centering_blocks.size() - 4);
		for (char& i : begin) {
			if (i != 'c') {
				flag = false;
				break;
			}
		}
	};
	std::string answer = "";
	for (int i = 0; i < centering_blocks.size(); i++) {
		answer += "alignment of ";
		answer += std::to_string(i + 1);
		answer += " block:";
		if (centering_blocks[i] == 'c')
			answer += "center\n";
		else {
			if (centering_blocks[i] == 'r')
				answer += "right\n";
			else {
				if (centering_blocks[i] == 'l')
					answer += "left\n";
				else
					answer += "not found\n";
			}
		}
	}
	if (flag)
		answer += "\nThe title page corresponds to standart";
	else
		answer += "\nThe title page is not corresponds to standart";
	return answer;
}

bool title_check::check_centering_text(const int& x_left, const int& x_right, const int& sheet_width,
	const int& admission, const int& dpi) {
	if (std::abs((x_left - (dpi / 25.4) * 30) - (sheet_width - ((dpi / 25.4) * 10) - x_right)) < admission)
		return true;
	else
		return false;
}
bool title_check::check_centering_right_text(const int& x_left, const int& x_right, const int& sheet_width,
	const int& admission, const int& dpi) {
	if (std::abs(sheet_width - ((dpi / 25.4) * 10) - x_right) < admission)
		return true;
	else
		return false;
}

bool title_check::check_centering_left_text(const int& x_left, const int& x_right, const int& sheet_width,
	const int& admission, const int& dpi) {
	if (std::abs(((dpi / 25.4) * 30) - x_left) < admission)
		return true;
	else
		return false;
}
