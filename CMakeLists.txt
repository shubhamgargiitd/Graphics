cmake_minimum_required(VERSION 3.16)
project(VectorEditor)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For clangd
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON) # Important for Signals/Slots

# Find Qt6 (or Qt5)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Svg)

#compile and link the source files to create the executable. The source files are located in the src directory and the header files are located in the include directory.
file(GLOB SOURCES "src/*.cpp" "src/tools/*.cpp" "src/tools/individual_tools/*.cpp" "src/file_actions/*.cpp" "src/file_actions/serializer_and_parser_for_tools/*.cpp" "src/file_actions/parser_for_individual_shapes/*.cpp" "src/utils/*.cpp" "src/shapes/*.cpp")
file(GLOB HEADERS "include/*.h" "include/shape/*.h" "include/tools/*.h" "include/tools/individual_tools/*.h" "include/file_actions/*.h"  "include/utils/*.h")

add_executable(VectorEditor ${SOURCES} ${HEADERS})

#Link the Qt libraries to executable.
target_link_libraries(VectorEditor PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Svg)

#search for headers in the include directory
target_include_directories(VectorEditor PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Copy icons directory to build directory
file(COPY ${CMAKE_SOURCE_DIR}/icons DESTINATION ${CMAKE_BINARY_DIR})

# Install icons with the executable
install(DIRECTORY ${CMAKE_SOURCE_DIR}/icons DESTINATION .)

