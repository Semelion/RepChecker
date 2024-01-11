add_library(intervales intervales.cpp include/intervales/intervales.hpp)
set_property(TARGET intervales PROPERTY CXX_STANDARD 20)

target_include_directories(intervales PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS intervales)
target_link_libraries(intervales ${OpenCV_LIBS} rectangles classify_blocks)
