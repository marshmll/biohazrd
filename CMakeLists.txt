cmake_minimum_required(VERSION 3.16)
project(BIOHAZRD LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(COPY src/Assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY src/Config DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY src/Fonts DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY src/Maps DESTINATION ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(BIOHAZRD src/main.cpp)
add_subdirectory(src)

target_link_libraries(BIOHAZRD PRIVATE sfml-graphics)
target_compile_features(BIOHAZRD PRIVATE cxx_std_17)

target_include_directories(BIOHAZRD PRIVATE include)
target_include_directories(BIOHAZRD PRIVATE include/Components)
target_include_directories(BIOHAZRD PRIVATE include/Engine)
target_include_directories(BIOHAZRD PRIVATE include/Entities)
target_include_directories(BIOHAZRD PRIVATE include/Entities/Enemies)
target_include_directories(BIOHAZRD PRIVATE include/GUI)
target_include_directories(BIOHAZRD PRIVATE include/Items)
target_include_directories(BIOHAZRD PRIVATE include/Items/MeleeWeapons)
target_include_directories(BIOHAZRD PRIVATE include/Items/RangedWeapons)
target_include_directories(BIOHAZRD PRIVATE include/States)
target_include_directories(BIOHAZRD PRIVATE include/States/EditorModes)
target_include_directories(BIOHAZRD PRIVATE include/Tiles)
target_include_directories(BIOHAZRD PRIVATE include/TileMap)
target_include_directories(BIOHAZRD PRIVATE include/Utils)

target_precompile_headers(BIOHAZRD PRIVATE include/stdafx.h)

if(WIN32)
    add_custom_command(
        TARGET BIOHAZRD
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:BIOHAZRD>
        VERBATIM)
endif()

install(TARGETS BIOHAZRD)