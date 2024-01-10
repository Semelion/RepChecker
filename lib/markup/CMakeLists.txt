cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


include("C:/Users/User/vcpkg_new/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE "C:/Users/User/vcpkg_new/scripts/buildsystems/vcpkg.cmake")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project ("poppler_1")

find_package(PkgConfig)
pkg_check_modules(POPPLER_CPP REQUIRED IMPORTED_TARGET poppler-cpp)
add_executable (poppler_test poppler_1.cpp)
target_link_libraries(poppler_test PRIVATE PkgConfig::POPPLER_CPP)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET poppler_test PROPERTY CXX_STANDARD 20)
endif()
