#include <pdf2img/pdf2img.h>

pdf2img::pdf2img(const poppler::document* mypdf, int DPI){
  capacity_ = mypdf->pages();
  data_ = new cv::Mat [capacity_];

  for(int i = 0; i < mypdf->pages(); i++){
    poppler::page* mypage = mypdf->create_page(i);
      poppler::page_renderer renderer;
      renderer.set_render_hint(poppler::page_renderer::text_antialiasing);
      poppler::image myimage = renderer.render_page(mypage, DPI, DPI);

      // std::cout << "created image of  " << myimage.width() << "x"<< myimage.height() << "\n";
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

cv::Mat& pdf2img::operator[] (const std::ptrdiff_t i){
  if (i < 0 || i >= capacity_)
      throw std::out_of_range("Wrong Index");
  return *(data_ + i);
}

ptrdiff_t pdf2img::get_size(){
  return capacity_;
}
