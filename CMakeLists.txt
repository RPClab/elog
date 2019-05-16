# CMakeLists.txt for ELOG project
project(ELOG)
cmake_minimum_required(VERSION 2.8)

# compile options
option(USE_SSL  "Use OpenSSL library for https" ON)
option(USE_KRB5 "Use Kerberos library for authentication" OFF)
option(USE_LDAP "Use LDAP library for authentication" OFF)
option(USE_PAM  "Use PAM library for authentication" OFF)

#----------------------------------

include_directories(${CMAKE_SOURCE_DIR}/mxml)

# default compiler flags
add_compile_options(-Wall -Wno-deprecated-declarations)

# disable warnings for regex.c
set_source_files_properties(${CMAKE_SOURCE_DIR}/src/regex.c PROPERTIES COMPILE_FLAGS -w)

# Package finders
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# optional SSL library
if (USE_SSL)
  add_compile_definitions(HAVE_SSL)
  find_package(OPENSSL REQUIRED)
  include_directories(${OPENSSL_INCLUDE_DIR})
endif (USE_SSL)

# optional KRB5 library
if (USE_KRB5)
  add_compile_definitions(HAVE_KRB5)
  find_package(KRB5 REQUIRED)
  include_directories(${KERBROS5_INCLUDE_DIR})
endif (USE_KRB5)

# optional LDAP library
if (USE_LDAP)
  add_compile_definitions(HAVE_LDAP)
  find_package(LDAP REQUIRED)
  include_directories(${LDAP_INCLUDE_DIR})
endif (USE_LDAP)

# optional PAM library
if (USE_PAM)
  add_compile_definitions(HAVE_PAM)
  find_package(PAM REQUIRED)
  include_directories(${PAM_INCLUDE_DIR})
endif (USE_PAM)

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

if(USE_SSL)
  target_link_libraries(elogd ${OPENSSL_LIBRARIES})
  target_link_libraries(elog ${OPENSSL_LIBRARIES})
endif(USE_SSL)
if(USE_KRB5)
  target_link_libraries(elogd ${KRB5_LIBRARIES})
endif(USE_KRB5)
if(USE_LDAP)
  target_link_libraries(elogd ${LDAP_LIBRARIES})
endif(USE_LDAP)
if(USE_PAM)
  target_link_libraries(elogd ${PAM_LIBRARIES})
endif(USE_PAM)
