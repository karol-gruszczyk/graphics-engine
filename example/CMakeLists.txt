file(COPY res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(example main.cpp)
target_link_libraries(example LINK_PUBLIC bauasian glfw ${GLFW_LIBRARIES})
