#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-page-renderer.h>
#include <poppler-image.h>
#include <vector>
#include <string>
#include <cmath>
#include <cfenv>
#include <climits>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/imgcodecs.hpp>
#include <nlohmann/json.hpp>

#include <pdf2img/pdf2img.h>
#include <text_recognition/text_recognition.hpp>
#include <check_format.hpp>
#include <rectangles/rectangles.hpp>
#include <title_check/title_check.hpp>
#include <indents.hpp>

int main(int argc, char* argv[]){

	std::ifstream f(argv[1]);
	nlohmann::json config = nlohmann::json::parse(f);
	// std::cout << config["file_path"] << '\n';

	poppler::document* mypdf = poppler::document::load_from_file(config["file_path"]);

	if (mypdf == NULL) {
		std::cerr << "couldn't read pdf\n";
	}
	pdf2img images_from_pdf(mypdf, 300);

	std::vector<cv::Mat> doc;
	for (int i = 0; i < images_from_pdf.get_size(); i++) {
		doc.push_back(images_from_pdf[i]);
	}
	CutRectangles rectangles(doc);

	nlohmann::json output;
	std::string out_path = config["output_path"];
	std::ofstream output_file(out_path);

	//формат
	{
		std::vector<std::string> isPages = isFormat(images_from_pdf);
		std::vector<int> format_errors;
		for (int i = 0; i < isPages.size(); i++) {
			//std::cout << "page " << i + 1 << " format is " << isPages[i] << std::endl;
			if("not found" == isPages[i]){
				format_errors.push_back(i);
			}
		}
		if(format_errors.size() > 0)
			output["wrong format pages"] = format_errors;
		else
			output["wrong format pages"] = "all pages is good";

	}

	 // std::cout << output << std::endl;

	//отступы
	// std::vector<std::vector<double>> imagesIndents = checkIndents(images_from_pdf);
	// for (int i = 0; i < imagesIndents.size(); i++) {
	// 	std::cout << "page " << i + 1 << " | ";
	// 	std::cout << "left indent = " << imagesIndents[i][0] << " | ";
	// 	std::cout << "right indent = " << imagesIndents[i][1] << " | ";
	// 	std::cout << "top indent = " << imagesIndents[i][2] << " | ";
	// 	std::cout << "bottom indent = " << imagesIndents[i][3] << " | ";
	// 	std::cout << std::endl;
	// }

	//титульник

	title_check checking_title(rectangles[0], images_from_pdf[0].rows, images_from_pdf[0].cols, 300,100);
	// std::cout << "______----_______" << '\n';
	// std::cout << checking_title.get_result() << '\n';
	output["title_check"] = checking_title.get_result();


	output_file <<std::setw(4) << output << std::endl;
}
