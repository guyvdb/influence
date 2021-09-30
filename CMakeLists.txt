cmake_minimum_required (VERSION 3.5)




# -----------------------------------------------------------------
# Set project variables
# -----------------------------------------------------------------
set(PROJECT "Influence")
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(LIBS_DIR "${ROOT_DIR}/sources/libs")
set(EXEC_DIR "${ROOT_DIR}/sources/exec")
set(BIN_DIR "${ROOT_DIR}/bin")
set(BUILD_DIR "${ROOT_DIR}/build")

# -----------------------------------------------------------------
# Set project
# -----------------------------------------------------------------
project(${PROJECT})


# -----------------------------------------------------------------
# Compilter Options
# -----------------------------------------------------------------

set(CMAKE_C_STANDARD 99)
#add_compile_definitions("-g")

# cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
# set(PROJECT_NAME "MyLib" CXX)
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# project(${PROJECT_NAME})

# include(${CMAKE_SOURCE_DIR}/Sources.cmake) 
# set(SOURCE_FILES ${COMMON_CPP_FILES} ${COMMON_H_FILES})

# include_directories(include)

# add_compile_options("$<$<CONFIG:Debug>:/EHa /MTd /W3 /w14640>")

# add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})


message(STATUS "Compiler Options: ${CMAKE_C_FLAGS}" )


# -----------------------------------------------------------------
# Print out variables
# -----------------------------------------------------------------
message(STATUS "======================")
message(STATUS "Project: ${PROJECT}")
message(STATUS "Libs: ${LIBS_DIR}")
message(STATUS "Exec: ${EXEC_DIR}")
message(STATUS "Bin: ${BIN_DIR}")



# -----------------------------------------------------------------
# Add subdirectories
# -----------------------------------------------------------------

# binaries
add_subdirectory("${EXEC_DIR}/workbench")


# libraries
add_subdirectory("${LIBS_DIR}/graph")



