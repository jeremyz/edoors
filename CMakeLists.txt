cmake_minimum_required(VERSION 2.6)
project(edoors)
set(EDOORS_VERSION_MAJOR 0)
set(EDOORS_VERSION_MINOR 0)
set(EDOORS_VERSION_MICRO 1)
set(EDOORS_VERSION ${EDOORS_VERSION_MAJOR}.${EDOORS_VERSION_MINOR}.${EDOORS_VERSION_MICRO})

set(PACKAGE ${CMAKE_PROJECT_NAME})
set(PACKAGE_VERSION ${EDOORS_VERSION_MAJOR}.${EDOORS_VERSION_MINOR}.${EDOORS_VERSION_MICRO})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# debug
IF(WANT_DEBUG)
    SET(CMAKE_BUILD_TYPE Debug)
    SET(EDOORS_HAVE_DEBUG TRUE)
ELSE()
    SET(CMAKE_BUILD_TYPE Release)
    SET(EDOORS_HAVE_DEBUG FALSE)
ENDIF()

# c flags
SET(CMAKE_C_FLAGS "-O2")
SET(CMAKE_C_FLAGS_RELEASE "")
SET(CMAKE_C_FLAGS_DEBUG "-g -Winline")

# requirements
include(FindCompilerAttribute)
find_package(Eina REQUIRED)
include(EFLCheck)

# definitions
ADD_DEFINITIONS(-DPACKAGE_BIN_DIR="${CMAKE_INSTALL_PREFIX}/bin"
   -DPACKAGE_DATA_DIR="${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
   -DPACKAGE_LIB_DIR="${CMAKE_INSTALL_PREFIX}/src")

# CONFIG
ADD_DEFINITIONS(-DHAVE_CONFIG_H)
configure_file (
   "${PROJECT_SOURCE_DIR}/cmakeconfig.h.in"
   "${PROJECT_BINARY_DIR}/src/include/edoors_config.h"
   )
include_directories ("${PROJECT_BINARY_DIR}/src/include")

# subdirectories
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(doc)

