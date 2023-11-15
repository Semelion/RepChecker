add_library(text_recognition text_recognition.cpp include/text_recognition/text_recognition.hpp)
set_property(TARGET text_recognition PROPERTY CXX_STANDARD 20)
target_include_directories(text_recognition PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(text_recognition PUBLIC opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui Tesseract::libtesseract) 
install(FILES rus.traineddata DESTINATION .)
