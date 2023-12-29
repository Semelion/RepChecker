#include "include/check_format.hpp"

std::vector<std::string> isFormat(pdf2img imgs, double fault, double dpi) {
	std::vector<std::string> formats;
	double px_in_mm = dpi / 25.4;

	for (int i = 0; i < imgs.get_size(); i++) {
		if (abs(imgs[i].size().width - (105 * px_in_mm)) <= fault * px_in_mm && abs(imgs[i].size().height - (148 * px_in_mm)) <= fault * px_in_mm) {
			formats.push_back("A6");
		}
		else if (abs(imgs[i].size().width - (148 * px_in_mm)) <= fault * px_in_mm && abs(imgs[i].size().height - (210 * px_in_mm)) <= fault * px_in_mm) {
			formats.push_back("A5");
		}
		else if (abs(imgs[i].size().width - (210 * px_in_mm)) <= fault * px_in_mm && abs(imgs[i].size().height - (297 * px_in_mm)) <= fault * px_in_mm) {
			formats.push_back("A4");
		}
		else if (abs(imgs[i].size().width - (297 * px_in_mm)) <= fault * px_in_mm && abs(imgs[i].size().height - (420 * px_in_mm)) <= fault * px_in_mm) {
			formats.push_back("A3");
		}
		else if (abs(imgs[i].size().width - (420 * px_in_mm)) <= fault * px_in_mm && abs(imgs[i].size().height - (594 * px_in_mm)) <= fault * px_in_mm) {
			formats.push_back("A2");
		}
		else if (abs(imgs[i].size().width - (594 * px_in_mm)) <= fault * px_in_mm && abs(imgs[i].size().height - (841 * px_in_mm)) <= fault * px_in_mm) {
			formats.push_back("A1");
		}
		else if (abs(imgs[i].size().width - (841 * px_in_mm)) <= fault * px_in_mm && abs(imgs[i].size().height - (1189 * px_in_mm)) <= fault * px_in_mm) {
			formats.push_back("A0");
		}
		else {
			formats.push_back("not found");
		}
	}

	return formats;
}