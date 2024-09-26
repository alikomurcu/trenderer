cmake_minimum_required(VERSION 3.10)
project(MyOpenGLRenderer)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path for dependencies
set(DEPS_DIR "${CMAKE_SOURCE_DIR}/dependencies")

# Include directories for dependencies
include_directories(
    ${DEPS_DIR}/GLEW/include
    ${DEPS_DIR}/GLFW/include
    ${DEPS_DIR}/glm
    ${DEPS_DIR}/stb_image
)

# Link directories for dependencies (libraries)
link_directories(
    ${DEPS_DIR}/GLEW/lib/Release/x64
    ${DEPS_DIR}/GLFW/lib-vc2022
)

# Add source files for your project (you can modify the path)
set(SRC_FILES
    src/main.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/Mesh.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link GLEW, GLFW, OpenGL
target_link_libraries(${PROJECT_NAME} 
    opengl32
    glfw3
    glew32s
)

# For static linking with GLEW, you need to define this before linking
target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)


# Set working directory to project root (solutionDir)
set_target_properties(${PROJECT_NAME} PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Optional: Copy dependencies like DLLs for Windows
# if (WIN32)
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         "${DEPS_DIR}/GLEW/bin/glew32.dll"
#         $<TARGET_FILE_DIR:${PROJECT_NAME}>
#     )
# endif()
