#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-page-renderer.h>
#include <poppler-image.h>

//#include "lib\some_heck\some_check.h"

cv::Mat readPDFtoCV(const std::string& filename,int DPI) {
    poppler::document* mypdf = poppler::document::load_from_file(filename);

    if(mypdf == NULL) {
        std::cerr << "couldn't read pdf\n";
        return cv::Mat();
    }

    std::cout << "pdf has " << mypdf->pages() << " pages\n";

    poppler::page* mypage = mypdf->create_page(0);
    poppler::page_renderer renderer;
    renderer.set_render_hint(poppler::page_renderer::text_antialiasing);
    poppler::image myimage = renderer.render_page(mypage,DPI,DPI);

    std::cout << "created image of  " << myimage.width() << "x"<< myimage.height() << "\n";
    cv::Mat cvimg;
    if(myimage.format() == poppler::image::format_rgb24) {
        cv::Mat(myimage.height(),myimage.width(),CV_8UC3,myimage.data()).copyTo(cvimg);
    } else if(myimage.format() == poppler::image::format_argb32) {
        cv::Mat(myimage.height(),myimage.width(),CV_8UC4,myimage.data()).copyTo(cvimg);
    } else {
        std::cerr << "PDF format no good\n";
        return cv::Mat();
    }
    return cvimg;
}

int main(int argc, char* argv[]){
	for(int i = 0; i < argc; i++){
		std::cout << argv[i] << std::endl;
	}
	
	imshow("Display window", readPDFtoCV(argv[1], 300));
    int k = cv::waitKey(0);
}