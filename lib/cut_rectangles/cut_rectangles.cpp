#include <cut_rectangles/cut_rectangles.hpp>

CutRectangles::CutRectangles(const std::vector<cv::Mat>& images){
    pages_ = images;
    cv::Mat grayImage;
    for(int ind = 0; ind < pages_.size(); ++ind){
        cv::cvtColor(pages_[ind], grayImage, cv::COLOR_BGR2GRAY);
        cv::Mat projectionY = reducePageOy(grayImage);
        std::vector<cv::Rect> current_page_blocks = pre_count_blocks(projectionY, grayImage.cols, 1, ind);
        for(int rect_ind = 0; rect_ind < current_page_blocks.size(); ++rect_ind){
            cv::Mat cropped_image = grayImage(current_page_blocks[rect_ind]);
            cv::Mat projectionX = reducePageOx(cropped_image);
            cv::Rect currBlockOx = pre_count_blocks(projectionX, grayImage.rows, 0, ind)[0];
            current_page_blocks[rect_ind] = cv::Rect(cv::Point(currBlockOx.x, current_page_blocks[rect_ind].y), cv::Point(currBlockOx.x + currBlockOx.width, current_page_blocks[rect_ind].y + current_page_blocks[rect_ind].height));
            // cv::rectangle(pages_[ind], current_page_blocks[rect_ind], DEBUG_COLOR); // Debug
        }
        // cv::imshow("Result", pages_[ind]); Debug
        // cv::waitKey(0);
        rectangles_in_pages.push_back(current_page_blocks);
    }
}

cv::Mat CutRectangles::reducePageOy(const cv::Mat &image){
    cv::Mat projectionY;
    cv::reduce(image, projectionY, 1, cv::REDUCE_SUM, CV_32F);
    return projectionY;
}

cv::Mat CutRectangles::reducePageOx(const cv::Mat &image){
    cv::Mat projectionX;
    cv::reduce(image, projectionX, 0, cv::REDUCE_SUM, CV_32F);
    return projectionX;
}

std::vector<cv::Rect> CutRectangles::pre_count_blocks(cv::Mat projection, int missingDimension, int projection_type, int page){
    std::vector<cv::Rect> rectangles;
    if (projection_type == 1){ // OY
        // cv::Mat srcImage = pages_[page]; // Debug
        cv::Mat projectionY = projection;

        int max_projection_y = -1;
        for (int i = 0; i < projectionY.rows; ++i){
            max_projection_y = std::max(max_projection_y, projectionY.at<int>(i));
        }

        for(int i = 0; i < projectionY.rows; ++i){
            if(projectionY.at<int>(i) < max_projection_y){
                projectionY.at<int>(i) = 1;
            }
            else{
                projectionY.at<int>(i) = 0;
            }
        }

        int last_ind = -1, pix;
        bool fl = false;
        for(int pix_i = 0; pix_i < projectionY.rows; ++pix_i){
            pix = projectionY.at<int>(pix_i);
            if(!fl &&  pix == 1){
                fl = 1;
                last_ind = pix_i;
            }
            if(pix == 0 && fl){
                if((pix_i - 1) - last_ind + 1 <= RLSA_VALUE){
                    for(int i = last_ind; i < pix_i; ++i){
                        projectionY.at<int>(i) = 0;
                    }
                }
                fl = false;
            }
        }

        std::vector<cv::Point> textBoundsY;
        bool inTextY = false;

        for (int i = 0; i < projectionY.rows; i++) {
            int val = projectionY.at<int>(i);
            if (val && !inTextY) {
                inTextY = true;
                textBoundsY.push_back(cv::Point(0, i));
            } else if (val == 0 && inTextY) {
                inTextY = false;
                textBoundsY.push_back(cv::Point(0, i));
            }
        }

        for(int iter = 0; iter < textBoundsY.size(); iter += 2){
            rectangles.push_back(cv::Rect(textBoundsY[iter], cv::Point(missingDimension, textBoundsY[iter + 1].y)));
        }
    }
    else if (projection_type == 0){
        cv::Mat srcImage = pages_[page]; // Debug
        cv::Mat projectionX = projection;

        int max_projection_x = -1;
        for (int i = 0; i < projectionX.cols; ++i){
            max_projection_x = std::max(max_projection_x, projectionX.at<int>(i));
        }
        // 1 - text
        for(int i = 0; i < projectionX.cols; ++i){
            if(projectionX.at<int>(i) < max_projection_x){
                projectionX.at<int>(i) = 1;
            }
            else{
                projectionX.at<int>(i) = 0;
            }
        }

        int last_ind = -1, pix;
        bool fl = false;
        for(int pix_i = 0; pix_i < projectionX.cols; ++pix_i){
            pix = projectionX.at<int>(pix_i);
            if(!fl &&  pix == 0){
                fl = 1;
                last_ind = pix_i;
            }
            if(pix == 1 && fl){
                if((pix_i - 1) - last_ind + 1 <= RLSA_VALUE){
                    for(int i = last_ind; i < pix_i; ++i){
                        projectionX.at<int>(i) = 1;
                    }
                }
                fl = false;
            }
        }

        std::vector<cv::Point> textBoundsX;
        bool inTextX = false;

        for (int i = 0; i < projectionX.cols; i++) {
            int val = projectionX.at<int>(i);
            if (val && !inTextX) {
                inTextX = true;
                textBoundsX.push_back(cv::Point(i, 0));
            } else if (val == 0 && inTextX) {
                inTextX = false;
                textBoundsX.push_back(cv::Point(i, 0));
            }
        }

        rectangles.push_back(cv::Rect(textBoundsX[0], textBoundsX[textBoundsX.size() - 1]));
        // cv::rectangle(srcImage, rectangles[0], DEBUG_COLOR); // Debug 
        // cv::imshow("Result", srcImage);
        // cv::waitKey(0);
    }

    return rectangles;
}

std::vector<std::vector<cv::Rect> > CutRectangles::get_rectangles(){
    return rectangles_in_pages;
}
