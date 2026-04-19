cmake_minimum_required(VERSION 3.16)

project(kv C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Put the final executable in /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.c	
)

add_executable(kv ${SRC_FILES})

# Tell compiler where headers live for #include <kv.h>
target_include_directories(kv PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
)

target_compile_options(kv PRIVATE
    -Wall
	-Wextra
	-Wpedantic
)

add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kv
	DEPENDS kv
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
