#include "include/indents.hpp"

std::vector<std::vector<double>> checkIndents(pdf2img imgs, double dpi) {
	std::vector<int> notWhiteColor{ 254, 254, 254 };
	std::vector<std::vector<double>> result;
	double px_in_mm = dpi / 25.4;

	for (int i = 0; i < imgs.get_size(); i++) {
		double maxIndentsRow1 = imgs[i].cols + 1;
		double maxIndentsRow2 = imgs[i].cols + 1;
		double maxIndentsCol1 = imgs[i].rows + 1;
		double maxIndentsCol2 = imgs[i].rows + 1;


		for (int row = 0; row < imgs[i].rows; row++) {
			for (int col = 0; col < imgs[i].cols; col++) {
				cv::Vec3b& color = imgs[i].at<cv::Vec3b>(row, col);

				if (color[0] < notWhiteColor[0] && color[1] < notWhiteColor[1] && color[2] < notWhiteColor[2]) {
					if (maxIndentsRow1 > col) {
						maxIndentsRow1 = col;
					}
					break;
				}
			}

			for (int col = imgs[i].cols - 1; col >= 0; col--) {
				cv::Vec3b& color = imgs[i].at<cv::Vec3b>(row, col);

				if (color[0] < notWhiteColor[0] && color[1] < notWhiteColor[1] && color[2] < notWhiteColor[2]) {
					if (maxIndentsRow2 > (imgs[i].cols - 1) - col) {
						maxIndentsRow2 = (imgs[i].cols - 1) - col;
					}
					break;
				}
			}
		}

		for (int col = 0; col < imgs[i].cols; col++) {
			for (int row = 0; row < imgs[i].rows; row++) {
				cv::Vec3b& color = imgs[i].at<cv::Vec3b>(row, col);

				if (color[0] < notWhiteColor[0] && color[1] < notWhiteColor[1] && color[2] < notWhiteColor[2]) {
					if (maxIndentsCol1 > row) {
						maxIndentsCol1 = row;
					}
					break;
				}
			}

			for (int row = imgs[i].rows - 1; row >= 0; row--) {
				cv::Vec3b& color = imgs[i].at<cv::Vec3b>(row, col);

				if (color[0] < notWhiteColor[0] && color[1] < notWhiteColor[1] && color[2] < notWhiteColor[2]) {
					if (maxIndentsCol2 > (imgs[i].rows - 1) - row) {
						maxIndentsCol2 = (imgs[i].rows - 1) - row;
					}
					break;
				}
			}
		}

		result.push_back({ maxIndentsRow1 / px_in_mm, maxIndentsRow2 / px_in_mm, maxIndentsCol1 / px_in_mm, maxIndentsCol2 / px_in_mm });
	}

	return result;
}