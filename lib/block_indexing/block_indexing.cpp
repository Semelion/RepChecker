#include <block_indexing/block_indexing.hpp>

Block_indexing::Block_indexing(pdf2img& doc_imgs, CutRectangles& text_boxes){
  setlocale(LC_ALL,"ru_RU.UTF-8");
  for(int i = 0; i < doc_imgs.get_size(); i++){
    for(int j = 0;j < text_boxes[i].size()/3; j++){
        cv::Mat croppedImage = doc_imgs[i](text_boxes[i][j]);
        std::string rec = RecognizeText(croppedImage);
        // std::transform(rec.begin(), rec.end(), rec.begin(), std::tolower);
        // for(int i = 0; i < rec.size(); i++){
        //   rec[i] = towlower(rec[i]);
        // }
        std::string tmp;
        for(int i = 0; i < 9;i++)
          tmp += rec[i];

        if("Оглавление" == rec || "Содержание" == rec){
          indexes["content_list"]["in_dock"] = true;
          indexes["content_list"]["start"] = i;
          if(j != 0){
            errors_["main_blocks"]["content_list"] = "error, content list header not on top";
          }
          if(i == 0){
            errors_["main_blocks"]["title"] = "Haven't title";
            indexes["have_title_page"] = false;
          }else{
            indexes["have_title_page"] = true;
          }
        }else if("Введение" == rec){
          indexes["main_part"]["in_dock"] = true;
          if(indexes["content_list"]["in_dock"]){
            indexes["content_list"]["end"] = i - 1;
          }
          if(j != 0){
            errors_["main_blocks"]["main_part"] = "error, main part header not on top";
          }
        }else if("Список литературы" == rec || "Источники" == rec){
          indexes["sources"]["in_dock"] = true;
          if(indexes["main_part"]["in_dock"]){
            indexes["main_part"]["end"] = i - 1;
          }
          if(j != 0){
            errors_["main_blocks"]["sources"] = "error, sources header not on top";
          }
        }else if("Приложение" == tmp){
          indexes["extra_part"]["in_dock"] = true;
          if(indexes["sources"]["in_dock"]){
            indexes["sources"]["end"] = i - 1;
          }
          if(j != 0){
            errors_["main_blocks"]["extra_part"] = "error, extra_part header not on top";
          }
        }

        // std::cout << rec << '\n';
        // cv::imshow("ddd", croppedImage);
        // cv::waitKey(0);

    }
  }
}

nlohmann::json Block_indexing::get_indexing(){
  return indexes;
}
nlohmann::json Block_indexing::get_errors(){
  return errors_;
}
