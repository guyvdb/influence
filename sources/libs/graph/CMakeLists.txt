
#------------------------------------------------------------------------

# The executables name
set(LIBNAME "graph")

# List of sources
set(SOURCES
  private/graph.c
  private/tx.c
  private/vertex.c
  private/edge.c
  private/page.c
  private/store.c
  )

# List of includes
set(INCLUDES
  public/graph_types.h
  public/graph.h
  public/tx.h
  public/vertex.h
  public/edge.h

  private/page.h
  private/store.h
  )

#------------------------------------------------------------------------

# Add the library
add_library(${LIBNAME} SHARED ${SOURCES} ${INCLUDES})

# Output library name
message(STATUS "libname: lib${LIBNAME}.so")

# Set include directories
target_include_directories(${LIBNAME} PUBLIC public)
target_include_directories(${LIBNAME} PRIVATE private)

# Copy executable to build/bin
SET(BUILD_BIN_FILENAME "${BUILD_DIR}/bin/lib${LIBNAME}.so")
ADD_CUSTOM_COMMAND(TARGET ${LIBNAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  $<TARGET_FILE:${LIBNAME}>
  ${BUILD_BIN_FILENAME}
  COMMENT "Copy: lib${LIBNAME}.so -> ${BUILD_BIN_FILENAME}")

# Copy executable to ROOT/bin
SET(BIN_FILENAME "${BIN_DIR}/lib${LIBNAME}.so")
ADD_CUSTOM_COMMAND(TARGET ${LIBNAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  $<TARGET_FILE:${LIBNAME}>
  ${BIN_FILENAME}
  COMMENT "Copy: lib${LIBNAME}.so -> ${BIN_FILENAME}")

#------------------------------------------------------------------------
 
