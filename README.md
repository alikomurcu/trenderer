# Trenderer

Trenderer is a powerful and efficient rendering engine designed to handle complex graphics and animations with ease. This project aims to provide high-quality rendering capabilities for various applications, including games, simulations, and visualizations.

## Features
(TODO:)
- High-performance rendering
- Support for various graphics APIs (e.g., OpenGL, DirectX, Vulkan)
- Real-time lighting and shading
- Advanced animation system
- Cross-platform compatibility

## Installation

To install Trenderer, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/trenderer.git
    ```
2. Navigate to the project directory:
    ```sh
    cd trenderer
    ```
3. Build the project using your preferred build system (e.g., CMake, Makefile).

4. For building with cmake, 
    ``` sh
    mkdir build && cd build
    cmake .. # Run cmake
    cmake --build . # Build project
    # And run project from root directory, e.g.,
    cd ..
    ./build/<config>/<exetutable name>
    ```


## Compiling Assimp - If Needed
Compile assimp with these flags
``` sh
cmake CMakeLists.txt -DASSIMP_BUILD_STATIC_LIB=ON -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Debug -DASSIMP_BUILD_ZLIB=ON
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

For any questions or inquiries, please contact me at [alikomurcu32430@gmail.com](mailto:alikomurcu32430@gmail.com).
