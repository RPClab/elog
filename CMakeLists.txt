# CMakeLists.txt for ELOG project
project(ELOG)
cmake_minimum_required(VERSION 3.0)

# compile options
option(USE_SSL  "Use OpenSSL library for https" ON)
option(USE_KRB5 "Use Kerberos library for authentication" OFF)
option(USE_LDAP "Use LDAP library for authentication" OFF)
option(USE_PAM  "Use PAM library for authentication" OFF)

# install directory
set(CMAKE_INSTALL_PREFIX /usr/local)
set(ELOGDIR  ${CMAKE_INSTALL_PREFIX}/elog)
set(RCDIR    /etc/rc.d/init.d)
set(SRVDIR   /usr/lib/systemd/system)

#----------------------------------

include_directories(${CMAKE_SOURCE_DIR}/mxml)

# default compiler flags
if (!MSVC)
  add_compile_options(-W -Wall -Wno-deprecated-declarations)
endif()
if (MSVC)
  add_compile_options(/D_CRT_SECURE_WARNINGS /wd4005 /wd4244 /wd4267 /wd4996 /nologo)
endif()

# find git
find_package(Git)

# git revision file
set(GIT_REVISION ${CMAKE_SOURCE_DIR}/src/git-revision.h)

# disable warnings for regex.c
set_source_files_properties(${CMAKE_SOURCE_DIR}/src/regex.c PROPERTIES COMPILE_FLAGS -w)

# Package finders
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# optional SSL library
if (USE_SSL)
  add_definitions(-DHAVE_SSL)
  find_package(OpenSSL REQUIRED)
  include_directories(${OPENSSL_INCLUDE_DIR})
endif (USE_SSL)

# optional KRB5 library
if (USE_KRB5)
  add_definitions(-DHAVE_KRB5)
  find_package(KRB5 REQUIRED)
  include_directories(${KERBROS5_INCLUDE_DIR})
endif (USE_KRB5)

# optional LDAP library
if (USE_LDAP)
  add_definitions(-DHAVE_LDAP)
  find_package(LDAP REQUIRED)
  include_directories(${LDAP_INCLUDE_DIR})
endif (USE_LDAP)

# optional PAM library
if (USE_PAM)
  add_compile_definitions(HAVE_PAM)
  find_package(PAM REQUIRED)
  include_directories(${PAM_INCLUDE_DIR})
endif (USE_PAM)

set(GIT_REVISION_TMP ${GIT_REVISION}.tmp)

if (WIN32)
add_custom_target(git_revision_h
  COMMAND ${CMAKE_SOURCE_DIR}/makegit.bat
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_REVISION_TMP} ${GIT_REVISION}
  COMMAND ${CMAKE_COMMAND} -E remove ${GIT_REVISION_TMP}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/
)
else(WIN32)
add_custom_target(git_revision_h
  COMMAND ${CMAKE_SOURCE_DIR}/makegit > ${GIT_REVISION_TMP}
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_REVISION_TMP} ${GIT_REVISION}
  COMMAND ${CMAKE_COMMAND} -E remove ${GIT_REVISION_TMP}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/
)
endif()

add_executable(elogd 
  ${CMAKE_SOURCE_DIR}/src/elogd.c
  ${CMAKE_SOURCE_DIR}/src/auth.c
  ${CMAKE_SOURCE_DIR}/mxml/mxml.c
  ${CMAKE_SOURCE_DIR}/mxml/strlcpy.c
  ${CMAKE_SOURCE_DIR}/src/crypt.c
  ${CMAKE_SOURCE_DIR}/src/regex.c
)

add_executable(elog
  ${CMAKE_SOURCE_DIR}/src/elog.c
  ${CMAKE_SOURCE_DIR}/src/crypt.c
  ${CMAKE_SOURCE_DIR}/mxml/strlcpy.c
)

add_dependencies(elogd git_revision_h)
add_dependencies(elog git_revision_h)

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

if (WIN32)
   target_link_libraries(elogd wsock32 ws2_32)
   target_link_libraries(elog wsock32 ws2_32)
endif()

install(TARGETS elog 
        DESTINATION bin)
install(TARGETS elogd 
        DESTINATION sbin)
install(FILES ${CMAKE_SOURCE_DIR}/man/elog.1
        DESTINATION man/man1)
install(FILES ${CMAKE_SOURCE_DIR}/man/elogd.8
        DESTINATION man/man8)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/scripts
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_SOURCE_DIR}/themes
        MESSAGE_NEVER
        DESTINATION ${ELOGDIR})
install(FILES ${CMAKE_SOURCE_DIR}/ssl/server.crt
        ${CMAKE_SOURCE_DIR}/ssl/server.key
        DESTINATION ${ELOGDIR}/ssl/)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/logbooks/demo
        MESSAGE_NEVER
        DESTINATION ${ELOGDIR}/logbooks)

# only install elogd.cfg if not existing
set(COPY_ELOGD_CFG "cp -n ${CMAKE_SOURCE_DIR}/elogd.cfg.example ${ELOGDIR}/elogd.cfg")
install(CODE "execute_process(COMMAND ${COPY_ELOGD_CFG})")


if (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
install(FILES ${CMAKE_SOURCE_DIR}/elogd.plist
        DESTINATION /Library/LaunchDaemons/ch.psi.elogd.plist)

install(CODE "message(\"\nThe elogd servie can be started with:\")")
install(CODE "message(\"$ sudo launchctl load /Library/LaunchDaemons/ch.psi.elogd.plist\n\")")

#install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan 
#  \"$ sudo launchctl load /Library/LaunchDaemons/ch.psi.elogd.plist\")")
endif()

