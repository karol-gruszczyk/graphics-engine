cmake_minimum_required(VERSION 3.6)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(Boost COMPONENTS system filesystem REQUIRED)
link_libraries(${Boost_LIBRARIES})

find_path(freeimage_INCLUDE_DIRS FreeImage.h)
include_directories(${freeimage_INCLUDE_DIRS})
find_library(freeimage_LIBRARIES freeimage)
link_libraries(${freeimage_LIBRARIES})

file(GLOB_RECURSE SOURCES *.cpp)

add_library(engine ${SOURCES})
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Copy shader files
configure_file(engine/glsl/2d/basic_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/2d/basic_fs.glsl COPYONLY)
configure_file(engine/glsl/2d/basic_vs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/2d/basic_vs.glsl COPYONLY)
configure_file(engine/glsl/3d/globals.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/3d/globals.glsl COPYONLY)
configure_file(engine/glsl/3d/lights.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/3d/lights.glsl COPYONLY)
configure_file(engine/glsl/3d/phong_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/3d/phong_fs.glsl COPYONLY)
configure_file(engine/glsl/3d/phong_vs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/3d/phong_vs.glsl COPYONLY)
