# CMakeList.txt : CMake project for cpp_crawler, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("cpp_crawler")

# Add source to this project's executable.
add_executable (cpp_crawler "cpp_crawler.cpp" "cpp_crawler.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cpp_crawler PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
find_package(CURL CONFIG REQUIRED)
target_link_libraries(cpp_crawler PRIVATE CURL::libcurl)

find_package(unofficial-gumbo CONFIG REQUIRED)
target_link_libraries(cpp_crawler PRIVATE unofficial::gumbo::gumbo)