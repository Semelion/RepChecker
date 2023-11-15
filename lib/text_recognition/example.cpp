#include <iostream>
#include <string>
#include "text_recognition/text_recognition.hpp"


int main(int argc, char *argv[]) {
  std::cout << argv[1];
  std::string path = argv[1];
  cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
  std::cout << RecognizeText(img);
  return 0;
}