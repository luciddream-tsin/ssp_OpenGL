add_executable(03_triangle main.cpp)

# pthread dl 要在glfw3之后
target_link_libraries(03_triangle glad glfw3 pthread dl)