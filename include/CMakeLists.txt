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


macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB_RECURSE templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(${srcTemplatePath} ${destDir}/${templateFile} COPYONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(configure_files)

# Copy shader files
configure_files(${CMAKE_CURRENT_SOURCE_DIR}/bauasian/glsl/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glsl/)
