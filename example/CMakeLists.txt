find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_libraries(${GLUT_LIBRARY})

file(COPY res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(example main.cpp)
target_link_libraries(example LINK_PUBLIC bauasian)
