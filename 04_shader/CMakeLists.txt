add_executable(04_shader main.cpp Shader.cpp)

# pthread dl 要在glfw3之后
target_link_libraries(04_shader glad glfw3 pthread dl)