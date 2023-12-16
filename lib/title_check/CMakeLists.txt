add_library(title_check title_check.cpp include/title_check/title_check.hpp)
set_property(TARGET title_check PROPERTY CXX_STANDARD 20)
target_include_directories(title_check PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(title_check PUBLIC ${OpenCV_LIBS} rectangles) 
