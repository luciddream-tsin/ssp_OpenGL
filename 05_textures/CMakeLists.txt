add_executable(05_textures main.cpp Shader.cpp ../stb/stb_image.h)

# pthread dl 要在glfw3之后
target_link_libraries(05_textures glad glfw3 pthread dl)