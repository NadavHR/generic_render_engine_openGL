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

file(GLOB_RECURSE PROJECT_SOURCES "src/*.hpp" "src/*.cpp" )

file(GLOB_RECURSE ASSETS
    "src/assets/*"
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets/
        $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug/assets,${CMAKE_BINARY_DIR}/bin/Release/assets>
    DEPENDS ${ASSETS}
    COMMENT "Copying assets"
)
add_executable(generic_render_engine ${PROJECT_SOURCES} )
add_dependencies(generic_render_engine copy_assets)
# add_executable(generic_render_engine ${PROJECT_SOURCES})

target_link_libraries(generic_render_engine PRIVATE OpenGL::GL)
target_link_libraries(generic_render_engine PRIVATE glfw)
target_link_libraries(generic_render_engine PRIVATE glad::glad)
target_link_libraries(generic_render_engine PRIVATE glm::glm-header-only)
target_link_libraries(generic_render_engine PRIVATE assimp::assimp)

# Collect all directories under src/headers recursively
file(GLOB_RECURSE HEADER_DIRS LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/src/headers/*")

# Filter only directories (not files)
set(ALL_HEADER_DIRS "")
foreach(dir ${HEADER_DIRS})
    if(IS_DIRECTORY ${dir})
        list(APPEND ALL_HEADER_DIRS ${dir})
    endif()
endforeach()

target_include_directories(generic_render_engine PUBLIC
    "src/"
    "src/headers"
    ${ALL_HEADER_DIRS}
)
# Set preprocessor definitions and output directories based on build type
target_compile_definitions(generic_render_engine PRIVATE 
    $<$<CONFIG:Debug>:DEBUG_BUILD>
    $<$<CONFIG:Release>:NDEBUG>
)

set_target_properties(generic_render_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

