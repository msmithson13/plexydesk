PROJECT(PlexyDesk)

SET(LIB_MAJOR 0)
SET(LIB_MINOR 1)
SET(LIB_RELEASE 0)

SET(APPLICATION_NAME "${PROJECT_NAME}")
SET(APPLICATION_MAIN_VERSION "0.${LIB_MAJOR}.${LIB_MINOR}.${LIB_RELEASE}")

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
CMAKE_POLICY(SET CMP0003 NEW)

INCLUDE(CPack)

FIND_PACKAGE(Qt4 REQUIRED)

# This will cause cmake to include and link against the OpenGL module.
# Set all flags first and then use the QT_USE_FILE to set everything.
# Note that QT_USE_FILE also sets QT_DEFINITIONS
#SET(QT_USE_OPENGL TRUE)
INCLUDE(${QT_USE_FILE})

ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

INCLUDE_DIRECTORIES(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_SOURCE_DIR}
    ${QT_INCLUDE_DIR}
)

ADD_SUBDIRECTORY(lib)
#ADD_SUBDIRECTORY(src)
