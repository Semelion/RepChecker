cmake_minimum_required(VERSION 3.16)   

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 


project(RepChecker)


find_package(Tesseract CONFIG REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(PkgConfig)
pkg_check_modules(POPPLER_CPP REQUIRED IMPORTED_TARGET poppler-cpp)

add_subdirectory(lib)

add_executable(main main.cpp)
target_link_libraries(main ${OpenCV_LIBS} PkgConfig::POPPLER_CPP)

#target_link_libraries(main PRIVATE PkgConfig::POPPLER_CPP)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_docs DESTINATION .)
install(TARGETS main DESTINATION .)