cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(Boost COMPONENTS system filesystem REQUIRED)
link_libraries(${Boost_LIBRARIES})

find_path(freeimage_INCLUDE_FreeImage FreeImage.h)
include_directories(${freeimage_INCLUDE_FreeImage})
find_library(freeimage_LIBRARIES freeimage)
link_libraries(${freeimage_LIBRARIES})

find_library(assimp_LIBRARIES assimp)
link_libraries(${assimp_LIBRARIES})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
link_libraries(${FREETYPE_LIBRARIES})

file(GLOB_RECURSE SOURCES *.cpp)

add_library(bauasian ${SOURCES})
target_include_directories(bauasian PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Copy shader files
configure_file(bauasian/glsl/2d/basic_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/2d/basic_fs.glsl COPYONLY)
configure_file(bauasian/glsl/2d/basic_vs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/2d/basic_vs.glsl COPYONLY)
configure_file(bauasian/glsl/3d/globals.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/3d/globals.glsl COPYONLY)
configure_file(bauasian/glsl/3d/lights.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/3d/lights.glsl COPYONLY)
configure_file(bauasian/glsl/3d/phong_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/3d/phong_fs.glsl COPYONLY)
configure_file(bauasian/glsl/3d/phong_vs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/3d/phong_vs.glsl COPYONLY)
configure_file(bauasian/glsl/fonts/font_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/fonts/font_fs.glsl COPYONLY)
configure_file(bauasian/glsl/fonts/font_vs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/fonts/font_vs.glsl COPYONLY)
configure_file(bauasian/glsl/post_processing/basic_vs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/post_processing/basic_vs.glsl COPYONLY)
configure_file(bauasian/glsl/post_processing/kernel_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/post_processing/kernel_fs.glsl COPYONLY)
configure_file(bauasian/glsl/post_processing/large_kernel_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/post_processing/large_kernel_fs.glsl COPYONLY)
configure_file(bauasian/glsl/post_processing/black_white_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/post_processing/black_white_fs.glsl COPYONLY)
configure_file(bauasian/glsl/post_processing/blur_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/post_processing/blur_fs.glsl COPYONLY)
configure_file(bauasian/glsl/post_processing/fxaa_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/post_processing/fxaa_fs.glsl COPYONLY)
configure_file(bauasian/glsl/post_processing/fxaa/Fxaa3_11.h ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/post_processing/fxaa/Fxaa3_11.h COPYONLY)
configure_file(bauasian/glsl/sky/basic_vs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/sky/basic_vs.glsl COPYONLY)
configure_file(bauasian/glsl/sky/basic_fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/sky/basic_fs.glsl COPYONLY)
