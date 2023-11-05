#include "text_recognition/text_recognition.hpp"


std::string RecognizeText(const cv::Mat& im) {

  std::string outText;
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  
  api->Init(NULL, "rus", tesseract::OEM_LSTM_ONLY);
  api->SetPageSegMode(tesseract::PSM_AUTO);
  api->SetImage(im.data, im.cols, im.rows, 3, im.step);
  outText = std::string(api->GetUTF8Text());
  api->End();
  delete api;

  return outText;
}