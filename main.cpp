#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cfenv>
#include <climits>

#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-page-renderer.h>
#include <poppler-image.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <nlohmann/json.hpp>

#include <pdf2img/pdf2img.h>
#include <text_recognition/text_recognition.hpp>
#include <check_format.hpp>
#include <rectangles/rectangles.hpp>
#include <title_check/title_check.hpp>
#include <indents.hpp>
#include <block_indexing/block_indexing.hpp>
#include <intervales/intervales.hpp>

int main(int argc, char* argv[]){

	std::ifstream f(argv[1]);
	nlohmann::json config = nlohmann::json::parse(f);
	// std::cout << config["file_path"] << '\n';

	poppler::document* mypdf = poppler::document::load_from_file(config["file_path"]);

	if (mypdf == NULL) {
		std::cerr << "couldn't read pdf\n";
	}
	int dpi = config["dpi"];
	pdf2img images_from_pdf(mypdf, dpi);

	std::vector<cv::Mat> doc;
	for (int i = 0; i < images_from_pdf.get_size(); i++) {
		doc.push_back(images_from_pdf[i]);
	}
	CutRectangles rectangles(doc);


	nlohmann::json output;
	std::string out_path = config["output_path"];
	std::ofstream output_file(out_path);

	//Индексирование основных частей

	// Block_indexing indexes_(images_from_pdf, rectangles);
	// nlohmann::json main_part_index = indexes_.get_indexing();
	// output.push_back(indexes_.get_errors());

	//титульник
	double adm = config["title_admission"];
	title_check checking_title(rectangles[0], images_from_pdf[0].rows, images_from_pdf[0].cols, adm, dpi);
	output["title_check"] = checking_title.get_result();


	//формат
	{
	double fault = config["format_fault"];
	std::vector<std::string> isPages = isFormat(images_from_pdf, fault, dpi);
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

	//отступы
	{
	std::vector<int> error_pages;
	std::vector<std::vector<double>> imagesIndents = checkIndents(images_from_pdf);

	int fault = config["indents"]["fault"];
	int left_ind = config["indents"]["left"];
	int right_ind  = config["indents"]["right"];
	int up_ind  = config["indents"]["up"];
	int down_ind  = config["indents"]["down"];

	for (int i = 0; i < imagesIndents.size(); i++) {
		// std::cout << "page " << i + 1 << " | ";
		if ((abs(imagesIndents[i][0] - left_ind) <= fault || imagesIndents[i][0] >= left_ind) &&
			(abs(imagesIndents[i][1] - right_ind) <= fault || imagesIndents[i][1] >= right_ind) &&
			(abs(imagesIndents[i][2] - up_ind) <= fault || imagesIndents[i][2] >= up_ind) &&
			(abs(imagesIndents[i][3] - down_ind) <= fault || imagesIndents[i][3] >= down_ind)) {
			;
			// std::cout << "left indent = " << imagesIndents[i][0] << " | ";
			// std::cout << "right indent = " << imagesIndents[i][1] << " | ";
			// std::cout << "top indent = " << imagesIndents[i][2] << " | ";
			// std::cout << "bottom indent = " << imagesIndents[i][3] << " | ";
			// std::cout << " is compliant with the standard" << std::endl;

		}
		else {
			error_pages.push_back(i);
			// std::cout << "left indent = " << imagesIndents[i][0] << " | ";
			// std::cout << "right indent = " << imagesIndents[i][1] << " | ";
			// std::cout << "top indent = " << imagesIndents[i][2] << " | ";
			// std::cout << "bottom indent = " << imagesIndents[i][3] << " | ";
			// std::cout << " is not compliant with the standard" << std::endl;
		}
	}

	if(error_pages.size() > 0)
		output["wrong indents pages"] = error_pages;
	else
		output["wrong indents pages"] = "all pages is good";

	}

	// междустрочный интервал
	{
		Intervales intervales(doc);
		if(1 == intervales.check_intervale())
	  	output["intervales_in_doc"] = "OK";
		else
			output["intervales_in_doc"] = "NOT OK";
		output["averade_interval"] = 		intervales.get_avg_interval();

	std::vector<int> interv_med;
	for(int i = 0; i < images_from_pdf.get_size(); i++){
		interv_med.push_back(intervales.get_current_page_interval(i));
	}
	output["median_interval_of_every_pages"] = interv_med;

	}


	output_file << std::setw(4) << output << std::endl;
}
