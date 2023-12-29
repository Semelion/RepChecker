//! \file check_format.hpp
//! \authors Chekunova M.M.
//! \note Responsible: Polevoy D.V.

#ifndef CHECK_FORMAT_HPP_09_11_2023
#define CHECK_FORMAT_HPP_09_11_2023

#include<string>
#include<vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <pdf2img/pdf2img.h>

/**
\brief The function checks pages for sheet format.

 Input: imgs - cv::Mat array, fault - error in mm for sheet width and height, dpi - number of pixels per inch.
 Output: Sheet format values ​​(A1, A2, A3, A4, A5, A6, not found)
 */
std::vector<std::string> isFormat(pdf2img imgs, double fault = 3, double dpi = 300);

#endif