#include <intervales/intervales.hpp>


Intervales::Intervales(std::vector<cv::Mat> pages){
    pages_ = pages;
    CutRectangles rectangles(pages_);
    ClassifyRectangles clf(pages_, rectangles);

    std::map<int, int> lines_baselines;
    std::map<int, int> mx_box_heights;
    MedinasFromRunningData cur_page_medians;
    for(int temp_page = START_PAGE; temp_page < pages_.size(); ++temp_page){
        lines_baselines.clear();
        cur_page_medians.clear();

        for(int temp_line = 0; temp_line < rectangles[temp_page].size(); ++temp_line){
            int mx_ans = -1;
            int el_ans = 0;
            mx_box_heights.clear();
            cv::Mat current_line = pages_[temp_page](rectangles[temp_page][temp_line]);

            std::vector<cv::Rect> cur_parse = getIntervales(current_line);

            for(int temp_letter_parse = 0; temp_letter_parse < cur_parse.size(); ++temp_letter_parse){
                mx_box_heights[cur_parse[temp_letter_parse].y + cur_parse[temp_letter_parse].height] += 1;
            }
            for(auto& el: mx_box_heights){
                if (el.second > mx_ans){
                    mx_ans = el.second;
                    el_ans = el.first;
                }
            }
            lines_baselines[temp_line] = el_ans;
        }
        
        for(int i = 1; i < rectangles[temp_page].size() - 1; ++i){
            if(clf.at(temp_page, i - 1) == Label::text && clf.at(temp_page, i) == Label::text){
                int temp_curr_intervale = rectangles[temp_page][i].y + lines_baselines[i] - (rectangles[temp_page][i - 1].y + lines_baselines[i - 1]);
                cur_page_medians.push(temp_curr_intervale);
                sum_intervales_ += temp_curr_intervale;
                cnt_intervales_ += 1;
                // std::cout << temp_page << " page is ready " << i + 1 << " line is ready. " << "intervale " << rectangles[temp_page][i].y + lines_baselines[i] - (rectangles[temp_page][i - 1].y + lines_baselines[i - 1]) << std::endl;
            }
        }
        page_medians_.push_back(cur_page_medians);
    }
}

double Intervales::get_avg_interval(){
    return sum_intervales_ * 1.0 / cnt_intervales_;
}

double Intervales::get_current_page_interval(int page){
    if (page_medians_[page].getMedian() != -1){
        return page_medians_[page].getMedian();
    }
    return 0;
}

std::vector<cv::Rect> Intervales::getIntervales(cv::Mat line_in_rectangle){
    cv::Mat binary_line = line_in_rectangle;
    cv::cvtColor(line_in_rectangle, binary_line, cv::COLOR_BGR2GRAY);
    cv::Mat blurred;
    cv::GaussianBlur(binary_line, blurred, cv::Size(5, 5), 0);

    cv::Mat thresholded;
    cv::threshold(blurred, binary_line, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

    cv::Mat projectionX;
    cv::reduce(binary_line, projectionX, 0, cv::REDUCE_SUM, CV_32F);

    // 1 - text
    for(int i = 0; i < projectionX.cols; ++i){
        if(projectionX.at<int>(i) != 0){
            projectionX.at<int>(i) = 1;
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
            textBoundsX.push_back(cv::Point(i - 1, 0));
        }
    }

    if (textBoundsX.size() % 2 == 1){
        textBoundsX.push_back(cv::Point(line_in_rectangle.cols, 0));
    }

    std::vector<cv::Rect> parse_words;

    for(int iter = 0; iter < textBoundsX.size(); iter += 2){
        parse_words.push_back(cv::Rect(textBoundsX[iter], cv::Point(textBoundsX[iter + 1].x, line_in_rectangle.rows)));
    }

    std::vector<cv::Rect> parse_letter;

    for(int t_let = 0; t_let < parse_words.size(); ++t_let){ // create boxes
        parse_letter.clear();
        cv::Mat current_letter = line_in_rectangle(parse_words[t_let]);
        // cv::imshow("current_letter", current_letter);
        // cv::waitKey(0);
// ------------------------------------------- test line

        cv::Mat projectionY;
        cv::reduce(binary_line(parse_words[t_let]), projectionY, 1, cv::REDUCE_SUM, CV_32F);

        for(int i = 0; i < projectionY.rows; ++i){
            if(projectionY.at<int>(i) != 0){
                projectionY.at<int>(i) = 1;
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
        if (textBoundsY.size() % 2 == 1) {
            textBoundsY.push_back(cv::Point(0, projectionY.rows));
        }

        for(int iter = 0; iter < textBoundsY.size(); iter += 2){
            parse_letter.push_back(cv::Rect(textBoundsY[iter], cv::Point(line_in_rectangle.cols, textBoundsY[iter + 1].y)));
        }

        parse_words[t_let] = cv::Rect(parse_words[t_let].x, parse_letter[parse_letter.size() - 1].y, parse_words[t_let].width, parse_letter[parse_letter.size() - 1].height);


    }
    return parse_words;
}

bool Intervales::check_intervale(){
    MedinasFromRunningData median_of_medinas;
    for(int temp_page = 0; temp_page < pages_.size(); ++temp_page){
        if (get_current_page_interval(temp_page) == 0){
            continue;
        }
        median_of_medinas.push(get_current_page_interval(temp_page));
    }
    
    double val = median_of_medinas.getMedian() * TO_PT / 1.5 / 1.18;
    // std::cout << median_of_medinas.getMedian() * TO_PT / 1.5 / 1.18 << std::endl;
    if ((val > 13 && val < 15) || (val > 11 && val < 13)){
        return 1;  
    }
    return 0;
}