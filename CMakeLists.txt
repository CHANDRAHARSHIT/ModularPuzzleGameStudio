cmake_minimum_required(VERSION 3.10)
project(ModularPuzzleGameStudio)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML directory (works for both SFML 2.6 and 3.0)
if(EXISTS "C:/SFML/SFML-2.6.2-gcc15")
    set(SFML_DIR "C:/SFML/SFML-2.6.2-gcc15/lib/cmake/SFML")
    find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
elseif(EXISTS "C:/SFML/SFML-2.6.2")
    set(SFML_DIR "C:/SFML/SFML-2.6.2/lib/cmake/SFML")
    find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
elseif(EXISTS "C:/SFML/SFML-3.0.2")
    set(SFML_DIR "C:/SFML/SFML-3.0.2/lib/cmake/SFML")
    find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)
else()
    # Try to find SFML anywhere
    find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/core/*.cpp"
    "src/games/*.cpp"
    "src/ai/*.cpp"
    "src/observer/*.cpp"
    "src/util/*.cpp"
    "src/ui/*.cpp"
)

# Header files
file(GLOB_RECURSE HEADERS 
    "include/*.hpp"
    "include/core/*.hpp"
    "include/games/*.hpp"
    "include/ai/*.hpp"
    "include/observer/*.hpp"
    "include/util/*.hpp"
    "include/ui/*.hpp"
)

# Create executable
add_executable(GameStudio ${SOURCES} ${HEADERS})

# Link SFML libraries (compatible with both 2.x and 3.x)
if(SFML_VERSION VERSION_GREATER_EQUAL "3.0")
    target_link_libraries(GameStudio SFML::Graphics SFML::Window SFML::System)
else()
    target_link_libraries(GameStudio sfml-graphics sfml-window sfml-system)
endif()

# Link MinGW runtime statically to avoid DLL issues
if(MINGW)
    target_link_options(GameStudio PRIVATE -static-libgcc -static-libstdc++)
endif()

# Copy assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Installation
install(TARGETS GameStudio DESTINATION bin)
install(DIRECTORY assets DESTINATION bin)

# Platform-specific settings
if(WIN32)
    # Copy SFML DLLs on Windows
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(SFML_DLL_SUFFIX "-d")
    else()
        set(SFML_DLL_SUFFIX "")
    endif()
    
    # Add Windows-specific flags
    target_compile_definitions(GameStudio PRIVATE _WIN32_WINNT=0x0601)
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(GameStudio PRIVATE /W4)
else()
    target_compile_options(GameStudio PRIVATE -Wall -Wextra -pedantic)
endif()

# Print build information
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
