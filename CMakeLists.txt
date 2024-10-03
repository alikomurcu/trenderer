cmake_minimum_required(VERSION 3.10)
project(trenderer)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")  # Use /MD for dynamic linking

# Set the path for dependencies
set(DEPS_DIR "${CMAKE_SOURCE_DIR}/dependencies")

# Include directories for dependencies
include_directories(
    ${DEPS_DIR}/GLEW/include
    ${DEPS_DIR}/GLFW/include
    ${DEPS_DIR}/glm
    ${DEPS_DIR}/stb_image
    ${DEPS_DIR}/assimp/include
)

# Link directories for dependencies (libraries)
link_directories(
    ${DEPS_DIR}/GLEW/lib/Release/x64
    ${DEPS_DIR}/GLFW/lib-vc2022
    ${DEPS_DIR}/assimp/lib/Release
    ${DEPS_DIR}/assimp/contrib/zlib/Release
    ${DEPS_DIR}/assimp/lib/Debug
    ${DEPS_DIR}/assimp/contrib/zlib/Debug
)

# Add source files for your project (you can modify the path)
set(SRC_FILES
    src/Camera.cpp
    src/main.cpp
    src/Mesh.cpp
    src/Model.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/Transform.cpp    
)

# Add the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link GLEW, GLFW, OpenGL
# target_link_libraries(${PROJECT_NAME} 
#     opengl32
#     glfw3
#     glew32s
#     zlibstaticd
#     assimp-vc143-mtd
# )

#set the build type to debug
set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Debug configuration
    target_link_libraries(${PROJECT_NAME} 
        opengl32
        glfw3
        glew32s
        zlibstatic
        assimp-vc143-mtd  # Link the debug version of Assimp
    )
else()
    # Release configuration TODO: release mode gives error, fix it
    target_link_libraries(${PROJECT_NAME} 
        opengl32
        glfw3
        glew32s
        zlibstatic
        assimp-vc143-mt  # Link the release version of Assimp
    )
endif()
# For static linking with GLEW, you need to define this before linking
target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC ASSIMP_BUILD_STATIC)


# # Set the Assimp include directory
# include_directories(${DEPS_DIR}/assimp/include)

# # Set the Assimp library directories
# link_directories(${DEPS_DIR}/assimp/lib/Release)
# link_directories(${DEPS_DIR}/assimp/contrib/zlib/Release)

# # Add the Assimp and zlib libraries to the target
# target_link_libraries(${PROJECT_NAME} assimp-vc143-mt zlibstatic)

# Set working directory to project root (solutionDir)
set_target_properties(${PROJECT_NAME} PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)


# Copy all DLLs from vcpkg/bin to the build output directory for dynamic linking of assimp
# # Path to vcpkg's binary directory
# set(VCPKG_BIN_DIR "${CMAKE_SOURCE_DIR}/dependencies/assimp/installed/x64-windows/bin")

# # Output directory for the build (can be Debug, Release, etc.)
# set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/build/$(Configuration)/")

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#   "${VCPKG_BIN_DIR}"
#   "${OUTPUT_DIR}"
# )
