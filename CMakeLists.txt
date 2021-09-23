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



