cmake_minimum_required(VERSION 3.10)
project(ParallelFileCompressor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# --- Dependencies ---
find_package(ZLIB REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Qt6 COMPONENTS Core Widgets Charts REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# --- CLI Executable ---
add_executable(pfc
    src/main.cpp
    src/compressor.cpp
    src/decompressor.cpp
    src/benchmark.cpp
    src/utils.cpp
)
target_link_libraries(pfc PRIVATE ZLIB::ZLIB OpenMP::OpenMP_CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# --- GUI Executable ---
add_executable(pfc-gui
    src/main_gui.cpp
    src/compressor.cpp
    src/decompressor.cpp
    src/benchmark.cpp
    src/utils.cpp
    src/mainwindow.cpp
    src/compressionworker.cpp
    src/decompressionworker.cpp
    src/benchmarkworker.cpp
    src/progressdashboard.cpp
    src/logspanel.cpp
    src/splashscreen.cpp
    src/aboutdialog.cpp
    resources/resources.qrc

    include/mainwindow.hpp
    include/splashscreen.hpp
    include/aboutdialog.hpp
    include/logspanel.hpp
    include/progressdashboard.hpp
    include/compressionworker.hpp
    include/decompressionworker.hpp
    include/benchmarkworker.hpp


)

target_link_libraries(pfc-gui PRIVATE
    ZLIB::ZLIB
    OpenMP::OpenMP_CXX
    Qt6::Core
    Qt6::Widgets
    Qt6::Charts
)

message(STATUS "✅ Configuration Summary:")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "OpenMP: Found")
message(STATUS "ZLIB: Found")
message(STATUS "Qt6 (Core, Widgets, Charts): Found")
