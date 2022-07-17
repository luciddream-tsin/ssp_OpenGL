add_executable(07_coordinate_systems main.cpp Shader.cpp ../stb/stb_image.h)

# pthread dl 要在glfw3之后
target_link_libraries(07_coordinate_systems glad glfw3 pthread dl)