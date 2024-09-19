cmake_minimum_required(VERSION 3.28)
project(MarketTool)

set(CMAKE_CXX_STANDARD 17)

# Add CURL include directory
include_directories("C:/CURL/curl-8.10.1_1-win64-mingw/include")

# Add nlohmann/json include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add CURL library directory
link_directories("C:/CURL/curl-8.10.1_1-win64-mingw/lib")

# Add wxWidgets
set(wxWidgets_ROOT_DIR "C:/wxWidgets")
set(wxWidgets_LIB_DIR "C:/wxWidgets/lib/gcc_lib")

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Add your executable
add_executable(MarketTool main.cpp ChatGPTApi.cpp)

# Link CURL static or dynamic libraries (don't link both lib and dll versions)
target_link_libraries(MarketTool PRIVATE libcurl.lib)

# Link wxWidgets libraries
target_link_libraries(MarketTool PRIVATE ${wxWidgets_LIBRARIES})
