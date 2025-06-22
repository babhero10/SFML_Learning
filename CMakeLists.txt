cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

#    List all your source files here.
add_executable(gear_sim src/main.cpp src/Gear.cpp)

# 2. Link against ALL required SFML modules.
target_link_libraries(gear_sim PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# 3. Apply C++ standard to your new executable name
target_compile_features(gear_sim PRIVATE cxx_std_17)
