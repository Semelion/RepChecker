#include "include/indents.hpp"

std::vector<std::vector<double>> checkIndents(pdf2img imgs, double dpi) {
	std::vector<std::vector<double>> result;
	std::vector<cv::Mat> vector_imgs;
	double px_in_mm = dpi / 25.4;
	double footer_size_part = 0.0675;

	for (int i = 0; i < imgs.get_size(); i++) {
		vector_imgs.push_back(imgs[i]);
	}

	CutRectangles rectangles(vector_imgs);

	for (int i = 0; i < imgs.get_size(); i++) {
		double maxIndentsRow1 = imgs[i].cols + 1;
		double maxIndentsRow2 = imgs[i].cols + 1;
		double maxIndentsCol1 = imgs[i].rows + 1;
		double maxIndentsCol2 = imgs[i].rows + 1;
		bool is_was_footer_element = false;

		for (auto& rect : rectangles[i]) {
			if (maxIndentsRow1 > rect.x) {
				maxIndentsRow1 = rect.x;
			}

			if (maxIndentsRow2 > (imgs[i].cols - 1) - (rect.x + rect.width)) {
				maxIndentsRow2 = (imgs[i].cols - 1) - (rect.x + rect.width);
			}

			if (rect.y >= (imgs[i].rows - 1) * (1 - footer_size_part) && !is_was_footer_element) {
				is_was_footer_element = true;

				continue;
			}

			if (maxIndentsCol1 > rect.y) {
				maxIndentsCol1 = rect.y;
			}

			if (maxIndentsCol2 > (imgs[i].rows - 1) - (rect.y + rect.height)) {
				maxIndentsCol2 = (imgs[i].rows - 1) - (rect.y + rect.height);
			}
		}

		result.push_back({ maxIndentsRow1 / px_in_mm, maxIndentsRow2 / px_in_mm, maxIndentsCol1 / px_in_mm, maxIndentsCol2 / px_in_mm });
	}

	return result;
}