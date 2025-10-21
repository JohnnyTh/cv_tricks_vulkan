cmake_minimum_required(VERSION 3.26)
project(cv_tricks_vulkan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(cv_tricks_vulkan
        main.cpp)

target_link_libraries(
        cv_tricks_vulkan
        PRIVATE
        glfw
        Vulkan::Vulkan
        dl
        pthread
        X11
        Xrandr
        Xi
)
