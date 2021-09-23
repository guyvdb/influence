

#------------------------------------------------------------------------

# The executables name
set(EXECNAME "workbench")


# List of sources
set(SOURCES main.c)

# List of includes
set(INCLUDES "")

# List of libraries to link
set(LINKLIBS graph)



#------------------------------------------------------------------------

# Add the executable
add_executable(${EXECNAME} ${SOURCES})

target_link_libraries(${EXECNAME} ${LINKLIBS})


# Output exec name
message(STATUS "execname: ${EXECNAME}")

# Copy executable to build/bin
SET(BUILD_BIN_FILENAME "${BUILD_DIR}/bin/${EXECNAME}")
ADD_CUSTOM_COMMAND(TARGET ${EXECNAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  $<TARGET_FILE:${EXECNAME}>
  ${BUILD_BIN_FILENAME}
  COMMENT "Copy: ${EXECNAME} -> ${BUILD_BIN_FILENAME}")

# Copy executable to ROOT/bin
SET(BIN_FILENAME "${BIN_DIR}/${EXECNAME}")
ADD_CUSTOM_COMMAND(TARGET ${EXECNAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  $<TARGET_FILE:${EXECNAME}>
  ${BIN_FILENAME}
  COMMENT "Copy: ${EXECNAME} -> ${BIN_FILENAME}")

#------------------------------------------------------------------------

