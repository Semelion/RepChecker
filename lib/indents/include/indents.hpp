#ifndef INDENTS_HPP_01_12_2023
#define INDENTS_HPP_01_12_2023

#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <pdf2img/pdf2img.h>

std::vector<std::vector<double>> checkIndents(pdf2img img, double dpi = 300);

#endif