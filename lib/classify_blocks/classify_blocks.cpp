// #define DEBUG

#include "classify_blocks/classify_blocks.hpp"

std::vector<cv::Scalar> ClassifyRectangles::color_for_label{
  {0, 0, 255}, 
  {0, 128, 255},
  {0, 255, 128},
  {255, 255, 0},
  {255, 0, 0},
  {255, 51, 153},
  {255, 51, 255}
};

ClassifyRectangles::ClassifyRectangles(const std::vector<cv::Mat>& images, const CutRectangles& rectangles)
  : rectangles_ptr(&rectangles),
    pages(images) {
  std::vector<int> heights;
  rectangles_types.resize(rectangles.ssize());
  for (int i_page = 0; i_page < rectangles.ssize(); i_page += 1) {
    for (int i_rect = 0; i_rect < rectangles[i_page].size(); i_rect += 1) {
      heights.push_back(rectangles[i_page][i_rect].height);
    }
    rectangles_types[i_page].resize(rectangles[i_page].size());
  }

  double MeanBlocksHeight = 0;

  std::sort(heights.begin(), heights.end());

  if (heights.size() % 2) {
    MeanBlocksHeight = heights[heights.size() / 2];
  } else {
    MeanBlocksHeight = static_cast<double>(heights[heights.size() / 2 - 1] + heights[heights.size() / 2]) / 2;
  }

  for (int i_page = 0; i_page < rectangles.ssize(); i_page += 1) {
    
    cv::Mat gray_image;

    cv::cvtColor(images[i_page], gray_image, cv::COLOR_BGR2GRAY);

    cv::Mat black_and_white;

    cv::threshold(gray_image, black_and_white, 128, 255, cv::THRESH_BINARY);

    for (int i_rect = 0; i_rect < rectangles[i_page].size(); i_rect += 1) {

      // start extracting features

      cv::Mat cur_rect = black_and_white(rectangles[i_page][i_rect]);

      int N = NumberOfBlackPixels(cur_rect);

      int TH = HorizWhiteToBlackTransitions(cur_rect);

      int TV = VertWhiteToBlackTransitions(cur_rect);

      int delta_x = ColsWithBlackPixels(cur_rect);

      int height = rectangles[i_page][i_rect].height;

      int width = rectangles[i_page][i_rect].width;

      // count other features (based on previous)

      double R = static_cast<double>(width) / height;

      double D = N / static_cast<double>(width * height);

      double TH_X = static_cast<double>(TH) / delta_x;

      double TV_X = static_cast<double>(TV) / delta_x;

      double TH_Y = static_cast<double>(TH) / height;

      #ifdef DEBUG
        std::cout << "page number: " << i_page << " " << "rectangle number: " << i_rect << std::endl;
        std::cout << "x_min: " << rectangles[i_page][i_rect].x << std::endl;
        std::cout << "width: " << width << std::endl;
        std::cout << "y_min: " << rectangles[i_page][i_rect].y << std::endl;
        std::cout << "height: " << height << std::endl;
        std::cout << "delta_x: " << delta_x << std::endl;
        std::cout << "delta_x / dx: " << static_cast<double>(delta_x) / width << std::endl;
        std::cout << "TH: " << TH << std::endl;
        std::cout << "TV: " << TV << std::endl;
        std::cout << "TH_X: " << TH_X << std::endl;
        std::cout << "TV_X: " << TV_X << std::endl;
        std::cout << "N: " << N << std::endl;
        std::cout << "D: " << D << std::endl;
      #endif

      if (c1 * MeanBlocksHeight < height && height < c2 * MeanBlocksHeight) {
        rectangles_types[i_page][i_rect] = Label::text;
      } else if (height < c1 * MeanBlocksHeight && ch1 < TH_X && TH_X < ch2) {
        rectangles_types[i_page][i_rect] = Label::small_text;
      } else if (TH_X < ch3 && R > cr && c3 < TV_X && TV_X < c4) {
        rectangles_types[i_page][i_rect] = Label::horizontal_line;
      } else if (TH_X > 1 / ch3 && R < 1 / cr && c3 < TH_Y && TH_Y < c4) {
        rectangles_types[i_page][i_rect] = Label::vertical_line;
      } else if (height > c2 * MeanBlocksHeight && ch1 < TH_X && TH_X < ch2 && cv1 < TV_X && TV_X < cv2) {
        rectangles_types[i_page][i_rect] = Label::large_text;
      } else if (D < c5) {
        rectangles_types[i_page][i_rect] = Label::graphic;
      } else {
        rectangles_types[i_page][i_rect] = Label::picture;
      }

      #ifdef DEBUG
        std::cout << rectangles_types[i_page][i_rect] << std::endl;
        std::cout << "===============================================================================" << std::endl;
      #endif
    }
  } 
};

int ClassifyRectangles::NumberOfBlackPixels(const cv::Mat& img_area) {
  return img_area.rows * img_area.cols - cv::countNonZero(img_area);
};

int ClassifyRectangles::HorizWhiteToBlackTransitions(const cv::Mat& img_area) {
  int n_transitions = 0;
  for (int i_row = 0; i_row < img_area.rows; i_row += 1) {
    const uchar* p = img_area.ptr<uchar>(i_row);
    for (int i_col = 1; i_col < img_area.cols; i_col += 1) {
      if (p[i_col] == 0 && p[i_col - 1] == 255) { // 0 - black 255 - white
        n_transitions += 1;
      }
    }
  }
  return n_transitions;
};

int ClassifyRectangles::VertWhiteToBlackTransitions(const cv::Mat& img_area) {
  int n_transitions = 0;
  for (int i_row = 0; i_row < img_area.rows - 1; i_row += 1) {
    const uchar* p = img_area.ptr<uchar>(i_row);
    const uchar* n = img_area.ptr<uchar>(i_row + 1);
    for (int i_col = 0; i_col < img_area.cols; i_col += 1) {
      if (p[i_col] == 255 && n[i_col] == 0) { // 0 - black 255 - white
        n_transitions += 1;
      }
    }
  }
  return n_transitions;
};

int ClassifyRectangles::ColsWithBlackPixels(const cv::Mat& img_area) {
  int cnt_cols = 0;
  for (int i_col = 0; i_col < img_area.cols; i_col += 1) {
    if (img_area.rows != cv::countNonZero(img_area.col(i_col))) {
      cnt_cols += 1;
    }
  }
  return cnt_cols;
};

void ClassifyRectangles::PrintPageWithClassifiedRect(ptrdiff_t i_page) const {
  if (i_page < 0 || i_page >= pages.size()) {
    throw(std::out_of_range("page with whis index doesn't exist"));
  }
  cv::Mat copy;
  pages[i_page].copyTo(copy);
  for (int i_rect = 0; i_rect < (*rectangles_ptr)[i_page].size(); i_rect += 1) {
    Label cur_label = rectangles_types[i_page][i_rect];
    cv::rectangle(copy, (*rectangles_ptr)[i_page][i_rect], color_for_label[static_cast<int>(cur_label)], 3);
  }
  cv::imshow("result_of_classification", copy);
  cv::waitKey(0);
};

Label ClassifyRectangles::at(int i_page, int i_rect) const {
  if (i_page >= rectangles_types.size() || i_page < 0 || i_rect > rectangles_types[i_page].size() || i_rect < 0) {
    throw(std::out_of_range("wrong i_page or i_rect"));
  }
  return rectangles_types[i_page][i_rect];
}