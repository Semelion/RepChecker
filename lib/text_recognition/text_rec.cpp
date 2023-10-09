#include "include/text_rec.hpp"

void RecognizeText(std::string& imPath) {

  std::string outText;
  cv::Mat im = cv::imread(imPath, cv::IMREAD_COLOR);
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

  api->Init(NULL, "rus", tesseract::OEM_LSTM_ONLY);
  api->SetPageSegMode(tesseract::PSM_AUTO);
  api->SetImage(im.data, im.cols, im.rows, 3, im.step);
  outText = std::string(api->GetUTF8Text());
  std::ofstream ostrm;

  std::string file_name = "text.txt";

  ostrm.open(file_name);

  ostrm << outText;
  
  api->End();
  delete api;
  
}