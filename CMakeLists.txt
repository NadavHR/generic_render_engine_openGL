cmake_minimum_required(VERSION 3.10)

project(generic_render_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(assimp CONFIG REQUIRED)



file(GLOB_RECURSE PROJECT_SOURCES "src/*.hpp" "src/*.cpp")

# set(PROJECT_SOURCES "src/classes" "src/headers" "src")

add_executable(generic_render_engine ${PROJECT_SOURCES})

target_link_libraries(generic_render_engine PRIVATE OpenGL::GL)
target_link_libraries(generic_render_engine PRIVATE glfw)
target_link_libraries(generic_render_engine PRIVATE glad::glad)
target_link_libraries(generic_render_engine PRIVATE glm::glm-header-only)
target_link_libraries(generic_render_engine PRIVATE assimp::assimp)

target_include_directories(generic_render_engine PUBLIC 
        "src/" 
        "src/classes/" 
        "src/headers/" 
        "src/headers/render_objects/" 
        "src/headers/rendering/" 
        "src/headers/shading/" 
        "src/headers/shading/shaders")


add_custom_command(
        TARGET generic_render_engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/src/assets/
                ${CMAKE_CURRENT_BINARY_DIR}/assets/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

