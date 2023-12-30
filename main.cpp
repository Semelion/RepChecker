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

#include <pdf2img/pdf2img.h>
#include <text_recognition/text_recognition.hpp>
#include <check_format.hpp>
#include <rectangles/rectangles.hpp>
#include <title_check/title_check.hpp>
#include <indents.hpp>


int main(int argc, char* argv[]) {
	
	poppler::document* mypdf = poppler::document::load_from_file(argv[1]);
	//poppler::document* mypdf = poppler::document::load_from_file("C:/programms/sem3/projecto/RepChecker/test_docs/1.pdf");

	if (mypdf == NULL) {
		std::cerr << "couldn't read pdf\n";
	}
	pdf2img images_from_pdf(mypdf, 300);

	//формат
	std::vector<std::string> isPages = isFormat(images_from_pdf);
	for (int i = 0; i < isPages.size(); i++) {
		std::cout << "page " << i + 1 << " format is " << isPages[i] << std::endl;
	}

	std::cout << std::endl;

	//отступы
	std::vector<std::vector<double>> imagesIndents = checkIndents(images_from_pdf);
	for (int i = 0; i < imagesIndents.size(); i++) {
		std::cout << "page " << i + 1 << " | ";
		std::cout << "left indent = " << imagesIndents[i][0] << " | ";
		std::cout << "right indent = " << imagesIndents[i][1] << " | ";
		std::cout << "top indent = " << imagesIndents[i][2] << " | ";
		std::cout << "bottom indent = " << imagesIndents[i][3] << " | ";
		std::cout << std::endl;
	}

	//титульник
	std::vector<cv::Mat> doc;
	for (int i = 0; i < images_from_pdf.get_size(); i++) {
		doc.push_back(images_from_pdf[i]);
	}

	CutRectangles rectangles(doc);

	//std::vector<std::string> rec_text_from_boxes;//текст с прямоугольников
	//for (auto& i : rectangles[0]) {
	//	cv::Mat croppedImage = doc[0](i);
	//	SetConsoleOutputCP(CP_UTF8);
	//	rec_text_from_boxes.push_back(RecognizeText(croppedImage));
	//	/*std::cout << RecognizeText(croppedImage);
	//	cv::namedWindow("Image", cv::WINDOW_NORMAL);
	//	cv::imshow("Image", croppedImage);
	//	cv::waitKey(0);*/
	//}

	title_check checking_title(rectangles[0], images_from_pdf[0].rows, images_from_pdf[0].cols, 300, 100);
	std::cout << "______----_______" << '\n';
	std::cout << checking_title.get_result() << '\n';

	//распознавание текста
	//std::cout << argv[1];
	//std::string path = images_from_pdf;
	//cv::Mat img = cv::imread(images_from_pdf[0], cv::IMREAD_COLOR); 
}