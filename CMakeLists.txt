cmake_minimum_required(VERSION 3.1)

project(game)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(headers /usr/include)
find_package(SFML REQUIRED system window graphics)
if(!SFML_FOUND)
    message(">>> Installing sfml because it wasn't found")
    # Install SFML
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
endif()
target_link_libraries(${PROJECT_NAME} -lsfml-graphics -lsfml-window -lsfml-system)
