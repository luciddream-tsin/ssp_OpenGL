add_executable(01_window main.cpp)

# pthread dl 要在glfw3之后
target_link_libraries(01_window glad glfw3 pthread dl)