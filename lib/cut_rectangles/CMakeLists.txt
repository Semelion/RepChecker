add_library(cut_rectangles cut_rectangles.cpp include/cut_rectangles/cut_rectangles.hpp)
set_property(TARGET cut_rectangles PROPERTY CXX_STANDARD 20)
target_include_directories(cut_rectangles PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(cut_rectangles ${OpenCV_LIBS}) 
install(TARGETS cut_rectangles)