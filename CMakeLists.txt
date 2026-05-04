cmake_minimum_required(VERSION 3.20)
project(COS30008_Programming_Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# For MSYS2/MinGW builds, prefer toolchain-matching SFML package config.
# This avoids ABI/linker mismatches with prebuilt bundled libraries.
if(MINGW AND (NOT DEFINED SFML_DIR OR SFML_DIR MATCHES "-NOTFOUND$"))
    # Try common MSYS2 prefixes and both known SFML package-config layouts.
    set(_sfml_candidate_prefixes
        "C:/msys64/ucrt64"
        "C:/msys64/mingw64"
        "C:/msys64/clang64"
    )

    foreach(_prefix IN LISTS _sfml_candidate_prefixes)
        if(EXISTS "${_prefix}/lib/cmake/SFML/SFMLConfig.cmake")
            set(SFML_DIR "${_prefix}/lib/cmake/SFML")
            break()
        elseif(EXISTS "${_prefix}/lib/cmake/SFML3/SFMLConfig.cmake")
            set(SFML_DIR "${_prefix}/lib/cmake/SFML3")
            break()
        endif()
    endforeach()

    # Last-resort fallback: use bundled SFML package config if present.
    # Note: this may still fail at link/runtime if toolchain/ABI is incompatible.
    if(NOT DEFINED SFML_DIR AND EXISTS "${CMAKE_SOURCE_DIR}/external/SFML-3.0.1/lib/cmake/SFML/SFMLConfig.cmake")
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML-3.0.1/lib/cmake/SFML")
    endif()
endif()

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Prefer toolchain-matching SFML via package config (avoids ABI mismatch with MinGW/UCRT).
find_package(SFML 3 QUIET COMPONENTS Graphics Audio Window System)

if(SFML_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Audio SFML::Window SFML::System)
else()
    if(MINGW)
        message(FATAL_ERROR
            "SFML package not found for current MinGW toolchain.\n"
            "Install SFML for your active MSYS2 prefix, for example:\n"
            "  UCRT64 : pacman -S mingw-w64-ucrt-x86_64-sfml\n"
            "  MINGW64: pacman -S mingw-w64-x86_64-sfml\n"
            "  CLANG64: pacman -S mingw-w64-clang-x86_64-sfml\n"
            "or provide a compatible SFML via SFML_DIR.\n"
            "Bundled external/SFML-3.0.1 libs are likely built for a different toolchain/ABI.")
    endif()

    message(STATUS "SFML package not found; using bundled external/SFML-3.0.1 libraries.")
    target_include_directories(${PROJECT_NAME} PRIVATE external/SFML-3.0.1/include)
    target_link_directories(${PROJECT_NAME} PRIVATE external/SFML-3.0.1/lib)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:sfml-graphics-d sfml-audio-d sfml-window-d sfml-system-d>
        $<$<NOT:$<CONFIG:Debug>>:sfml-graphics sfml-audio sfml-window sfml-system>
    )
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/images $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/audio  $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/Roboto $<TARGET_FILE_DIR:${PROJECT_NAME}>/Roboto
)
