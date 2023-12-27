#ifndef CHECK_FORMAT_HPP_09_11_2023
#define CHECK_FORMAT_HPP_09_11_2023

#include<string>
#include<vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <pdf2img/pdf2img.h>

std::vector<std::string> isFormat(pdf2img img, double fault = 3, double dpi = 300);

#endif