#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <rectangles/rectangles.hpp>

#include <queue>
#include <vector>

using namespace std;


int main(){
    const int DPI = 300;
    constexpr double TO_PT = 72.0 / DPI;
    std::string document_path = "PATH"; // Use full path!
    cv::Mat srcImage;
    std::vector<cv::Mat> srcImages;
    std::filesystem::path my_path(document_path);
    for(auto& file: std::filesystem::directory_iterator(my_path)){
        if(file.path().string().find(".jpg") != std::string::npos){
        // if (file.path().string() == "/Users/klstepan67/Desktop/checker/pictures/4.jpg"){
            // std::cout << file.path() << std::endl;
            srcImage = cv::imread(file.path());
            srcImages.push_back(srcImage);
        }
    }
    long long su = 0;
    int cnt = 0;
    CutRectangles rectangles(srcImages);

    for(int p = 0; p < rectangles.ssize(); ++p){
        cv::Mat tempImage;
        tempImage = srcImages[p];
        for(auto& i: rectangles[p]){
            cv::rectangle(tempImage, i, cv::Scalar(0, 255, 0));
        }
        cv::imshow("debug", tempImage);
        cv::waitKey(0);
    }
}