add_executable(10_color main.cpp Camera.cpp Shader.cpp ../stb/stb_image.h)

# pthread dl 要在glfw3之后
target_link_libraries(10_color glfw3 glad )#pthread)# dl)