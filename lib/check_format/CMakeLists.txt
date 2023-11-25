add_library(check_format "check_format.cpp" "include/check_format.hpp")
set_property(TARGET check_format PROPERTY CXX_STANDARD 20)
target_include_directories(check_format PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(check_format PUBLIC opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui pdf2img) 