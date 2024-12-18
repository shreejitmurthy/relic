#[===[

cd build
cmake ..
cmake --build . --target Relic
./Relic

cmake --build . --target Relic && ./Relic

]===]

cmake_minimum_required(VERSION 3.28)
project(relic C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/cglm)

set(SOURCES
        vendor/glad/glad.c
        main.c
        source/core.c
        # source/graphics.c
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(OpenGL REQUIRED)

set(RELIC_COMMON_LIBS
        OpenGL::GL
        SDL3::SDL3
        cglm
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${RELIC_COMMON_LIBS})

target_compile_definitions(${PROJECT_NAME} PRIVATE LOG_USE_COLOR)
