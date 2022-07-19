add_executable(06_transformations main.cpp Shader.cpp ../stb/stb_image.h)

# pthread dl 要在glfw3之后
target_link_libraries(06_transformations glad glfw3 )# pthread dl)