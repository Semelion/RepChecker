add_library(block_indexing block_indexing.cpp include/block_indexing/block_indexing.hpp)
set_property(TARGET block_indexing PROPERTY CXX_STANDARD 20)

target_include_directories(block_indexing PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS block_indexing)
target_link_libraries(block_indexing ${OpenCV_LIBS} nlohmann_json::nlohmann_json pdf2img text_recognition rectangles)
