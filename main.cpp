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

// bool check_centering_text(int x_left, int x_right, int sheet_width,
// 	int dpi = 300, int admission = 100){
// 	//dpi/25.4 = 1mm
// 	//left 30 mm rigt 10 mm
// 	#if 0
// 		std::cout << "________________________________________" << '\n';
// 		std::cout << "x_left: " << x_left <<'\n';
// 		std::cout << "x_right: " << x_right <<'\n';
// 		std::cout << "sheet_width: " << sheet_width <<'\n';
// 		std::cout << "(x_left - (dpi/25.4)*30): " << (x_left - (dpi/25.4)*30) << '\n';
// 		std::cout << "(sheet_width - ((dpi/25.4)*10) - x_right): " << (sheet_width - ((dpi/25.4)*10) - x_right) << '\n';
// 	#endif
//
// 	if(std::abs((x_left - (dpi/25.4)*30) - (sheet_width - ((dpi/25.4)*10) - x_right)) < admission)
// 		return true;
// 	else
// 		return false;
// }
//
// bool check_centering_right_text(int x_left, int x_right, int sheet_width,
// 	int dpi = 300, int admission = 10){
// 		//std::abs((x_left - (dpi/25.4)*30) - (sheet_width - ((dpi/25.4)*10) - x_right))
// 		if(std::abs(sheet_width - ((dpi/25.4)*10) - x_right) < admission)
// 			return true;
// 		else
// 			return false;
// }

int main(int argc, char* argv[]){

	// for (int i = 0; i < argc; i++) {
	// 	std::cout << argv[i] << std::endl;
	// }

	poppler::document* mypdf = poppler::document::load_from_file(argv[1]);
	//poppler::document* mypdf = poppler::document::load_from_file("C:/programms/sem3/projecto/RepChecker-main/test_docs/example.pdf");
	if (mypdf == NULL) {
		std::cerr << "couldn't read pdf\n";
	}
	pdf2img images_from_pdf(mypdf, 300);
	//imwrite("1.jpg", images_from_pdf[0]);

	std::vector<std::string> isPages = isFormat(images_from_pdf);
	for (int i = 0; i < isPages.size(); i++) {
		std::cout << "page " << i + 1 << " format is " << isPages[i] << std::endl;
	}

	std::cout << std::endl;

	std::vector<std::vector<double>> imagesIndents = checkIndents(images_from_pdf);
	for (int i = 0; i < imagesIndents.size(); i++) {
		std::cout << "page " << i + 1 << " | ";
		std::cout << "left indent = " << imagesIndents[i][0] << " | ";
		std::cout << "right indent = " << imagesIndents[i][1] << " | ";
		std::cout << "top indent = " << imagesIndents[i][2] << " | ";
		std::cout << "bottom indent = " << imagesIndents[i][3] << " | ";
		std::cout << std::endl;
	}

	std::vector<cv::Mat> doc;
	for (int i = 0; i < images_from_pdf.get_size(); i++) {
		doc.push_back(images_from_pdf[i]);
	}

	CutRectangles rectangles(doc);

	//cv::Mat tempImage;
	//tempImage = doc[0];
	//std::vector<int> centering_blocks;
	//for(auto& i: rectangles[0]){
	//		cv::rectangle(tempImage, i, cv::Scalar(0, 255, 0), 5);
	//		std::cout << "C: " << check_centering_text(i.x, i.x + i.width, tempImage.cols, 300, 100)
	//		<< " R: " << check_centering_right_text(i.x, i.x + i.width, tempImage.cols) << '\n';
	//		if(check_centering_text(i.x, i.x + i.width, tempImage.cols))
	//			centering_blocks.push_back(1);
	//		else
	//			centering_blocks.push_back(-1);

	//		cv::imshow("debug", tempImage);
	//		cv::waitKey(0);
	//}
	//for(auto& i: centering_blocks)
	//	std::cout << i << '\n';
	//std::cout << "_______________________________" << '\n';
	//std::cout << std::count(centering_blocks.begin(), centering_blocks.end(), -1) << '\n';
	//if(centering_blocks[0] == 1 && 1 == centering_blocks[1] &&
	//	std::count(centering_blocks.begin(), centering_blocks.end(), -1) >= 4 &&
	//	centering_blocks[centering_blocks.size() - 1] == 1 && centering_blocks[centering_blocks.size() - 2] == 1){
	//		std::cout << "good title" << '\n';
	//}else{
	//	std::cout << "wrong title" << '\n';
	//}
	//title_check ddd();
	title_check checking_title(rectangles[0], images_from_pdf[0].rows, images_from_pdf[0].cols, 300,100);
	std::cout << "______----_______" << '\n';
	std::cout << checking_title.get_result() << '\n';
	//// cv::imshow("debug", tempImage);
	//cv::waitKey(0);

	// for(int p = 0; p < rectangles.ssize(); ++p){
	// 		cv::Mat tempImage;
	// 		tempImage = doc[p];
	// 		for(auto& i: rectangles[p]){
	// 				cv::rectangle(tempImage, i, cv::Scalar(0, 255, 0), 5);
	// 		}
	// 		cv::imshow("debug", tempImage);
	// 		cv::waitKey(0);
	// }

	// std::cout << "AAAAAAAA" << '\n';
	// for(int i = 0; i < doc.size()/3; i++){
	// 	cv::imshow("rect_", doc[i]);
	// 	cv::waitKey(0);
	// }

	//CutRectangles rect(doc);

	//CutRectangles rectangles(images_from_pdf[0]); // Конструктор принимает cv::Mat вектор изображений
	// std::vector<std::vector<cv::Rect> > all_rec = rect.get_rectangles(); // возвращает вектор векторов прямоугольников -> первый вектор - страницы
	// int k = rectangles[0].size(); // можно обращаться по индексу страницы

	// cv::Mat img = images_from_pdf[0];
	// //cv::rectangle(img, all_rec[0][3], cv::Scalar(0, 255, 0),3);
	//
	// for(int j = 0; j < rect[0].size(); j++){
	// 	cv::rectangle(img, rect[0][j], cv::Scalar(0, 255, 0),3);
	// }
	// for(int j = 0; j < all_rec[4].size(); j++){
	// 	cv::rectangle(img, all_rec[4][j], cv::Scalar(0, 0, 255),3);
	// }
	// cv::Point point1(0, 357);
	// cv::Point point2(img.cols - 1, 357);
	// cv::line(img, point1  , point2, cv::Scalar(0, 0, 255), 10);
	// cv::imshow("ddld", img);
	// cv::waitKey(0);
	// for(int i = 0; i < images_from_pdf.get_size(); i++){
	// 	cv::Mat img = images_from_pdf[i];
	// 	for(int j = 0; j < rect[i].size(); j++){
	// 		cv::rectangle(img, rect[i][j], cv::Scalar(0, 255, 0));
	// 	}
	// 	cv::imshow("rect_", img);
	// 	cv::waitKey(0);
	// }

/////////////////////////
	// cv::Mat grey_title_page;
	// cv::cvtColor(images_from_pdf[0], grey_title_page, cv::COLOR_BGR2GRAY);
	//
	// // Поиск контуров текста на изображении
	// std::vector<std::vector<cv::Point>> contours;
	// cv::findContours(grey_title_page, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	// img = images_from_pdf[0];
	// for(int i = 0; i < contours.size(); i++){
	// 	// Вычисление прямоугольных границ текста
	// 	cv::Rect boundingBox = cv::boundingRect(contours[0]);
	// 	cv::rectangle(img, boundingBox, cv::Scalar(0, 255, 0),3);
	// }
	//
	// cv::imshow("title", img);
	// cv::waitKey(0);
	// // Определение выравнивания текста
	// // if (boundingBox.x < grey_title_page.cols / 2) {
	// //     std::cout << "LEFT" << '\n';
	// // } else if (boundingBox.x + boundingBox.width > grey_title_page.cols / 2) {
	// //     std::cout << "RIGHT" << '\n';
	// // } else {
	// //     std::cout << "CENTRE" << '\n';
	// // }
	//
	// std::vector<int> medium_bright_y;
	//
	// for(int y = 0; y < grey_title_page.rows; y++){
	// 	int temp = 0;
	// 	for(int x = 0; x < grey_title_page.cols; x++){
	// 		// if ((int)grey_title_page.at<uchar>(x, y) < 200)
	// 		// 	std::cout << (int)grey_title_page.at<uchar>(x, y) << "\t";
	//
	// 		temp += grey_title_page.at<uchar>(x, y);
	// 		// if(grey_title_page.at<uchar>(x, y) > 250)
	// 		// 	temp += grey_title_page.at<uchar>(x, y);
	// 		// 	grey_title_page.at<uchar>(x, y)=0;
	// 		//std::cout << grey_title_page.at<int>(x, y) << '  ';
	// 	}
	// 	// std::cout << '\n';
	// 	//double t = temp / grey_title_page;
	// 	medium_bright_y.push_back(static_cast<int>(temp) / grey_title_page.cols);
	// }
	// std::cout << grey_title_page.cols << '\n';
	// for(int i = 0; i < grey_title_page.cols; i++){
	// 	if((int)grey_title_page.at<uchar>(i, 357) != 255)
	// 		std::cout << (int)grey_title_page.at<uchar>(i, 357) << ' ';
	// }
	// // cv::imshow("origin", images_from_pdf[0]);
	// // cv::imshow("gr", grey_title_page);
  // // cv::waitKey(0);
	//
	// // cv::Mat vec_out(medium_bright_y.size() , 500, CV_8UC1 );
	// // for(int y = 0; y < vec_out.rows; y++){
	// // 	for(int x = 0; x < vec_out.cols; x++){
	// // 		vec_out.at<uchar>(x, y) = medium_bright_y[y];
	// // 		//std::cout << grey_title_page.at<int>(x, y) << '  ';
	// // 	}
	// // }
	// // cv::imshow("rect_", vec_out);
	// // cv::waitKey(0);
	//
	// std::cout << "_______________________________" << '\n';
	// std::cout << medium_bright_y.size() << "_____" << grey_title_page.rows << '\n';
	// int t = 0;
	// for(int i = 0; i < medium_bright_y.size(); i++) {
	// 		if(medium_bright_y[i] > t)
	// 			t = medium_bright_y[i];
	// }
	// std::cout << t << " - max\n";
	// t = 256;
	// for(int i = 0; i < medium_bright_y.size(); i++) {
	// 		if(medium_bright_y[i] < t)
	// 			t = medium_bright_y[i];
	// }
	// std::cout << t << " - min\n";
	// for(int i = 500; i < 530; i++){
	// 			 std::cout << medium_bright_y[i] << '\n';
	// }
	// cv::imshow("rect_", images_from_pdf[0]);
  // cv::waitKey(0);
//////////////////////////
	//распознавание текста
	/*std::cout << argv[1];
	std::string path = argv[1];
	cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
	std::cout << RecognizeText(img);
	*/

	//вырезанная картинка
	//cv::Rect roi(0, 0, images_from_pdf[0].size().width, images_from_pdf[0].size().height); // Пример: создаем прямоугольник, который задает область для вырезки (x, y, width, height)
	//std::cout << images_from_pdf[0].size().width << " " << images_from_pdf[0].size().height;

	//для названия образовательного учреждения
	/*float indentRx = (1 / 25.4) * 30;
	float sizeRecX = images_from_pdf[0].size().width - indentRx - (1 / 25.4) * 10;
	float indentRy = 0;
	float sizeRecY = 0;
	sizeRecY = 1000;
	cv::Rect roi(indentRx, indentRy, sizeRecX, sizeRecY);
	cv::Mat croppedImg = images_from_pdf[0](roi);*/

	//для года внизу
	// float startX = (300 / 25.4) * 30;
	// //startX = 0;
	// float indentRx = (300 / 25.4)*10;
	// float sizeRecX = images_from_pdf[0].size().width - startX -indentRx;
	// float startY = 2800;
	// //startY = 0;
	// float sizeRecY = images_from_pdf[0].size().height - startY;
	// cv::Rect roi(startX, startY, sizeRecX, sizeRecY);
	// cv::Mat croppedImg = images_from_pdf[0](roi);

	/*cv::Mat image_blurred_with_3x3_kernel;
	GaussianBlur(croppedImg, image_blurred_with_3x3_kernel, cv::Size(9, 9), 0);*/
	//cv::medianBlur(croppedImg, croppedImg, 9);


	//линия на изображении
	/*cv::Point startPoint1(0, croppedImg.rows / 2);
	cv::Point endPoint1(75 * 300 / 25.4, croppedImg.rows / 2);
	cv::Point startPoint2(croppedImg.cols - 1, croppedImg.rows / 2);
	cv::Point endPoint2(croppedImg.cols - 1 - 75 * 300 / 25.4, croppedImg.rows / 2);
	cv::line(croppedImg, startPoint2, endPoint2, cv::Scalar(0, 255, 0), 10);
	cv::line(croppedImg, startPoint1, endPoint1, cv::Scalar(0, 0, 255), 10);*/

	/*cv::Scalar lower_black = cv::Scalar(0, 0, 0);
	cv::Scalar upper_black = cv::Scalar(70, 70, 70);

	cv::Mat mask;
	cv::inRange(croppedImg, lower_black, upper_black, mask);

	int blackPixels = cv::countNonZero(mask);
	std::cout << blackPixels<<":black pix";

	int totalPixels = croppedImg.rows * croppedImg.cols;

	if (static_cast<double>(blackPixels) / totalPixels > 0.0) {
		std::cout << "black" << std::endl;
	}
	else {
		std::cout << "not" << std::endl;
	}*/

	//нахождение черных пикселей у вырезанного изображения
	//right pixel
	// float x2 = -1, y2 = -1;
	// for (int x = croppedImg.cols - 1; x >= 0; x--) {
	// 	for (int y = 0; y < croppedImg.rows; y++) {
	// 		cv::Vec3b pixel2 = croppedImg.at<cv::Vec3b>(y, x);
	// 		if (pixel2[0] == 0 && pixel2[1] == 0 && pixel2[2] == 0) {
	// 			x2 = x;
	// 			y2 = y;
	// 			break;
	// 		}
	// 	}
	// 	if (x2 != -1) {
	// 		break;
	// 	}
	// }
	// //left
	// float x1 = -1, y1 = -1;
	// for (int x = 0; x < croppedImg.cols; x++) {
	// 	for (int y = 0; y < croppedImg.rows; y++) {
	// 		cv::Vec3b pixel1 = croppedImg.at<cv::Vec3b>(y, x);
	// 		if (pixel1[0] == 0 && pixel1[1] == 0 && pixel1[2] == 0 && y==y2) {
	// 			x1 = x;
	// 			y1 = y;
	// 			break;
	// 		}
	// 	}
	// 	if (x1 != -1) {
	// 		break;
	// 	}
	// }
	//
	// std::cout << "croppedImg.cols:" << croppedImg.cols << std::endl;
	// std::cout << "croppedImg.rows:" << croppedImg.rows << std::endl;
	//
	// /*cv::Point point1(x1, y1);
	// cv::circle(croppedImg, point1, 10, cv::Scalar(255, 0, 0), -1);
	// cv::Point point2(x2, y2);
	// cv::circle(croppedImg, point2, 10, cv::Scalar(255, 0, 0), -1);*/
	//
	//
	// std::cout << x1 << " " << y1 << std::endl << x2 << " " << y2;
	// int fault = 10;
	// if (abs(x1 - (croppedImg.cols - 1 - x2)) < fault) {
	// 	std::cout << "centre";
	// }
	// else {
	// 	std::cout << "not centre";
	// }


	//выравнивание по середине
	//bool isTextCentered = false;
	//int centerY = croppedImg.rows / 2; // находим центральную строку изображения
	//for (int x = 0; x < croppedImg.cols / 2; x++) {
	//	cv::Vec3b pixelLeft = croppedImg.at<cv::Vec3b>(centerY, x);
	//	cv::Vec3b pixelRight = croppedImg.at<cv::Vec3b>(centerY, croppedImg.cols - 1 - x);
	//	if (pixelLeft[0] == 0 && pixelLeft[1] == 0 && pixelLeft[2] == 0 &&
	//		pixelRight[0] == 0 && pixelRight[1] == 0 && pixelRight[2] == 0) {
	//		isTextCentered = true;
	//		//break;  // если найдены черные пиксели с обеих сторон от центра, текст выравнен по центру
	//	}
	//}
	//if (isTextCentered) {
	//	std::cout << "centre" << std::endl;
	//}
	//else {
	//	std::cout << "not centre" << std::endl;
	//}

	//окно для вывода картинки
	//cv::imshow("Mask Image", mask);

	//cv::namedWindow("Cropped Image", cv::WINDOW_NORMAL); // Создаем окно для отображения изображения
	//cv::imshow("Cropped Image", croppedImg);
	//cv::imwrite("croped_page.png", croppedImg);
	//cv::waitKey(0); // Ждем, пока пользователь не нажмет клавишу (для закрытия окна)

	//cv::Mat image = croppedImg;
}
