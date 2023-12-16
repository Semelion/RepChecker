add_library(pdf2img pdf2img.cpp include/pdf2img/pdf2img.h)
set_property(TARGET pdf2img PROPERTY CXX_STANDARD 20)
target_include_directories(pdf2img PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(pdf2img PUBLIC ${OpenCV_LIBS} PkgConfig::POPPLER_CPP) 
