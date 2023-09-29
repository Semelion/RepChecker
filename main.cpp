#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-page-renderer.h>
#include <poppler-image.h>

//#include "lib\some_heck\some_check.h"
class pdf2img{
	public:
    explicit pdf2img(const std::string& filename,int DPI){
    	poppler::document* mypdf = poppler::document::load_from_file(filename);

	    if(mypdf == NULL) {
	        std::cerr << "couldn't read pdf\n";
	    }

	    std::cout << "pdf has " << mypdf->pages() << " pages\n";
	    capacity_ = mypdf->pages();
	    data_ = new cv::Mat [capacity_];

		for(int i = 0; i < mypdf->pages(); i++){
			poppler::page* mypage = mypdf->create_page(i);
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
		    }
		    *(data_ + i) = cvimg;
		}
    }


    cv::Mat& operator[] (const std::ptrdiff_t i)
	{
	    if (i < 0 || i >= capacity_)
	        throw std::out_of_range("Wrong Index");
	    return *(data_ + i);
	}
	ptrdiff_t get_size(){
		return capacity_;
	}
private:
    ptrdiff_t capacity_ = 0;
	cv::Mat* data_ = nullptr;
};

int main(int argc, char* argv[]){
	for(int i = 0; i < argc; i++){
		std::cout << argv[i] << std::endl;
	}
	pdf2img images_from_pdf(argv[1], 300);

	for(int i = 0; i < images_from_pdf.get_size(); i++){
		imshow("Display window", images_from_pdf[i]);
	    cv::waitKey(0);
	}
}