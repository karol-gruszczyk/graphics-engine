add_executable(example main.cpp)
target_link_libraries(example LINK_PUBLIC bauasian glfw ${GLFW_LIBRARIES} ${FREETYPE_LIBRARIES})
