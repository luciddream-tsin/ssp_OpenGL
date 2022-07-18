add_executable(08_camera main.cpp Shader.cpp Camera.cpp ../stb/stb_image.h)

# pthread dl 要在glfw3之后
target_link_libraries(08_camera glad glfw3 pthread dl)