add_library(indents "indents.cpp" "include/indents.hpp")
set_property(TARGET indents PROPERTY CXX_STANDARD 20)
target_include_directories(indents PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(indents PUBLIC opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui pdf2img) 