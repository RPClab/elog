message(STATUS "Resolving GIT Version")

set(_build_version "unknown")

find_package(Git)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} log -n 1 --pretty=format:"%ad - %h" --date=short
    WORKING_DIRECTORY "${local_dir}"
    OUTPUT_VARIABLE _build_version
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message( STATUS "GIT hash: ${_build_version}")
else()
  message(STATUS "GIT not found")
endif()

configure_file(${CMAKE_SOURCE_DIR}/cmake/git-revision.h.in ${CMAKE_BINARY_DIR}/generated/git-revision.h @ONLY)
