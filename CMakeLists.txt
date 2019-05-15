# CMakeLists.txt for ELOG project
project(ELOG)
cmake_minimum_required(VERSION 2.8)

# compile options
option(USE_SSL "Use OpenSSL library for https" OFF)

include_directories(${CMAKE_SOURCE_DIR}/mxml)

# default compiler flags
add_compile_options(-Wall -Wno-deprecated-declarations)

# disable warnings for regex.c
set_source_files_properties(${CMAKE_SOURCE_DIR}/src/regex.c PROPERTIES COMPILE_FLAGS -w)

# optional SSL stuff
if (USE_SSL)
  add_compile_definitions(HAVE_SSL)
  find_package(OPENSSL REQUIRED)
  include_directories(${OPENSSL_INCLUDE_DIR})
endif (USE_SSL)

add_executable(elogd 
  ${CMAKE_SOURCE_DIR}/src/elogd.c
  ${CMAKE_SOURCE_DIR}/src/auth.c
  ${CMAKE_SOURCE_DIR}/mxml/mxml.c
  ${CMAKE_SOURCE_DIR}/src/crypt.c
  ${CMAKE_SOURCE_DIR}/src/regex.c
)

add_executable(elog
  ${CMAKE_SOURCE_DIR}/src/elog.c
  ${CMAKE_SOURCE_DIR}/src/crypt.c
)

target_link_libraries(elogd ${OPENSSL_LIBRARIES})
target_link_libraries(elog ${OPENSSL_LIBRARIES})


