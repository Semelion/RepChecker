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

find_package(nlohmann_json CONFIG REQUIRED)

add_subdirectory(lib)

add_executable(main main.cpp)
target_link_libraries(main ${OpenCV_LIBS} PkgConfig::POPPLER_CPP nlohmann_json::nlohmann_json pdf2img text_recognition check_format rectangles title_check indents block_indexing intervales)

#target_link_libraries(main PRIVATE PkgConfig::POPPLER_CPP)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_docs DESTINATION .)
install(TARGETS main DESTINATION .)
install(FILES example.json DESTINATION .)

find_package(Doxygen)
option(BUILD_DOC "Build documentation" ON)

if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs DESTINATION .)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
