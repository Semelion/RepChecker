cmake_minimum_required(VERSION 3.12)
project(pdf2img)

set(CMAKE_CXX_STANDARD 20)

find_package(Poppler REQUIRED)

add_library(pdf2img STATIC pdf2img.cpp include/pdf2img/pdf2img.h)

target_include_directories(pdf2img PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(pdf2img PUBLIC Poppler::Poppler)
