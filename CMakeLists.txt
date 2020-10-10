cmake_minimum_required(VERSION 3.16)
project(PhongShadingDemo)

set(CMAKE_CXX_STANDARD 17)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(Vendor/GLFW)
add_subdirectory(Vendor/GL3W)
add_subdirectory(Vendor/GLM)

add_executable(PSD
        Source/main.cpp
        Source/Core/Shader.cpp
        Source/Core/Shader.h
        Source/Core/Application.cpp
        Source/Core/Application.h
        Source/Core/VertexArray.cpp
        Source/Core/VertexArray.h
        Source/ControlPanel.cpp
        Source/ControlPanel.h
        Source/PSD.h
        Vendor/ImGui/imgui.cpp
        Vendor/ImGui/imgui_draw.cpp
        Vendor/ImGui/imgui_widgets.cpp
        Vendor/ImGui/imgui_demo.cpp
        Vendor/ImGui/examples/imgui_impl_opengl3.cpp
        Vendor/ImGui/examples/imgui_impl_glfw.cpp)

# FIXME Symlinks sind sehr problematisch. Aber copy, copy_if_different und copy_directory übernehmen scheinbar keine Änderungen
add_custom_command(
        TARGET PSD PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/Resources" "${CMAKE_CURRENT_BINARY_DIR}/Resources"
)
target_include_directories(PSD PRIVATE
        Vendor/ImGui
        Vendor/ImGui/examples)
target_link_libraries(PSD
        gl3w
        glfw
        glm)

