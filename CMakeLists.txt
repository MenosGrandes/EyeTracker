cmake_minimum_required(VERSION 3.0)
#for YCM
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")
project (EyeTrakcer)
find_package (OpenCV REQUIRED)
find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy tbb_preview)
add_executable(EyeTrakcer main.cpp)
target_link_libraries(EyeTrakcer ${OpenCV_LIBS} tbb )
