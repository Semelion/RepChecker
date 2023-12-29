//! \file indents.hpp
//! \authors Chekunova M.M.
//! \note Responsible: Polevoy D.V.

#ifndef INDENTS_HPP_01_12_2023
#define INDENTS_HPP_01_12_2023

#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <pdf2img/pdf2img.h>
#include <rectangles/rectangles.hpp>

/**
\brief The function is designed to determine indentations in mm.

 Input: imgs - cv::Mat array, dpi - number of pixels per inch.
 Output: The padding values ​​for each sheet, specified as a two-dimensional vector.
 For each sheet, returns the margins on the left, right, top and bottom, respectively.
 */
std::vector<std::vector<double>> checkIndents(pdf2img imgs, double dpi = 300);

#endif