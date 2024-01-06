add_library(contentChecker contentChecker.cpp include/contentChecker/contentChecker.hpp)
set_property(TARGET contentChecker PROPERTY CXX_STANDARD 20)

target_include_directories(contentChecker PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS contentChecker)
target_link_libraries(contentChecker ${OpenCV_LIBS})
