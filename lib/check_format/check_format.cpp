#include "include/check_format.hpp"

std::vector<std::string> isFormat(pdf2img imgs) {
	const int fault = 3;
	std::vector<std::string> formats;

	for (int i = 0; i < imgs.get_size(); i++) {
		if (abs(imgs[i].size().width - 1240) <= fault && abs(imgs[i].size().height - 1748) <= fault) {
			formats.push_back("A6");
		}
		else if (abs(imgs[i].size().width - 1748) <= fault && abs(imgs[i].size().height - 2480) <= fault) {
			formats.push_back("A5");
		}
		else if (abs(imgs[i].size().width - 2480) <= fault && abs(imgs[i].size().height - 3508) <= fault) {
			formats.push_back("A4");
		}
		else if (abs(imgs[i].size().width - 3508) <= fault && abs(imgs[i].size().height - 4961) <= fault) {
			formats.push_back("A3");
		}
		else if (abs(imgs[i].size().width - 4961) <= fault && abs(imgs[i].size().height - 7016) <= fault) {
			formats.push_back("A2");
		}
		else if (abs(imgs[i].size().width - 7016) <= fault && abs(imgs[i].size().height - 9933) <= fault) {
			formats.push_back("A1");
		}
		else if (abs(imgs[i].size().width - 9933) <= fault && abs(imgs[i].size().height - 14043) <= fault) {
			formats.push_back("A0");
		}
		else {
			formats.push_back("not found");
		}
	}

	return formats;
}