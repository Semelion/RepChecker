add_library(rectangles rectangles.cpp include/rectangles/rectangles.hpp)
set_property(TARGET rectangles PROPERTY CXX_STANDARD 20)

target_include_directories(rectangles PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS rectangles)
target_link_libraries(rectangles ${OpenCV_LIBS})
