#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-page-renderer.h>
#include <poppler-image.h>

#include "lib\pdf2img.h"

int main(int argc, char* argv[]){
	for(int i = 0; i < argc; i++){
		std::cout << argv[i] << std::endl;
	}

	poppler::document* mypdf = poppler::document::load_from_file(argv[1]);
    if(mypdf == NULL) {
        std::cerr << "couldn't read pdf\n";
    }
	pdf2img images_from_pdf(mypdf, 300);
	imwrite("1.jpg", images_from_pdf[0]);
	imwrite("2.jpg", images_from_pdf[1]);
	imwrite("3.jpg", images_from_pdf[2]);
	// for(int i = 0; i < images_from_pdf.get_size(); i++){
	// 	imshow("Display window", images_from_pdf[i]);
	// 	imwrite(str(i) + ".jpg", mages_from_pdf[i]);  
	//     cv::waitKey(0);
	// }
}
