#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <intervales/intervales.hpp>
#include <vector>

using namespace std;

int main(){

    std::string document_path = "/Users/klstepan67/Desktop/checker/test_docs"; // Use full path!
    cv::Mat srcImage;
    std::vector<cv::Mat> srcImages;
    std::filesystem::path my_path(document_path);
    for(auto& file: std::filesystem::directory_iterator(my_path)){
        if(file.path().string().find("0.jpg") != std::string::npos){ //  && file.path().string().find("16.jpg") == std::string::npos){
        // if (file.path().string() == "/Users/klstepan67/Desktop/checker/pictures/4.jpg"){
            // std::cout << file.path() << std::endl;
            srcImage = cv::imread(file.path());
            srcImages.push_back(srcImage);
        }
    }

    Intervales intervales(srcImages);
    std::cout << intervales.check_intervale();
}