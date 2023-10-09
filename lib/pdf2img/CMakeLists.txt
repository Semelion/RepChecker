add_library(pdf2img "include/pdf2img.h")
set_property(TARGET pdf2img PROPERTY CXX_STANDARD 20)
target_include_directories(pdf2img PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(pdf2img PUBLIC opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui PkgConfig::POPPLER_CPP) 