#/*============================================================================
#
#  BARD: Basic Augmented Reality Demo.
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

######################################################################
# Set the minimum CMake version.
######################################################################
cmake_minimum_required(VERSION 3.1)


##################################################################################
# Set some CMake Policies.
# See http://cmake.org/cmake/help/cmake-2-8-docs.html#section_Policies for details
##################################################################################

set(project_policies
#  CMP0001 # NEW: CMAKE_BACKWARDS_COMPATIBILITY should no longer be used.
#  CMP0002 # NEW: Logical target names must be globally unique.
#  CMP0003 # NEW: Libraries linked via full path no longer produce linker search paths.
#  CMP0004 # NEW: Libraries linked may NOT have leading or trailing whitespace.
#  CMP0005 # NEW: Preprocessor definition values are now escaped automatically.
#  CMP0006 # NEW: Installing MACOSX_BUNDLE targets requires a BUNDLE DESTINATION.
#  CMP0007 # NEW: List command no longer ignores empty elements.
#  CMP0008 # NEW: Libraries linked by full-path must have a valid library file name.
#  CMP0009 # NEW: FILE GLOB_RECURSE calls should not follow symlinks by default.
#  CMP0010 # NEW: Bad variable reference syntax is an error.
#  CMP0011 # NEW: Included scripts do automatic cmake_policy PUSH and POP.
#  CMP0012 # NEW: if() recognizes numbers and boolean constants.
#  CMP0013 # NEW: Duplicate binary directories are not allowed.
#  CMP0014 # NEW: Input directories must have CMakeLists.txt
#  CMP0048 # NEW: Project specifies the version number.
#  CMP0053 # NEW: New references and variable expansion.
  )
foreach(policy ${project_policies})
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()


######################################################################
# We have a super-build option. 
######################################################################

option(BUILD_SUPERBUILD "Build BARD and the projects it depends on via SuperBuild.cmake." ON)

if (BUILD_SUPERBUILD)
  project(BARD-superbuild)
  set(BARD_SOURCE_DIR ${PROJECT_SOURCE_DIR})
  set(BARD_BINARY_DIR ${PROJECT_BINARY_DIR})
else()
  project(BARD VERSION 15.05.0)
endif()

######################################################################
# Setting supported build types. Should ONLY be Release or Debug.
######################################################################

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Valid options are Release or Debug" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug")
endif()

if (NOT (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Debug"))
  message(FATAL_ERROR "Build type \"${CMAKE_BUILD_TYPE}\" is not supported.")
endif()

if(WIN32)
  # Restrict the generated configuration to be what we configured above.
  # No point creating project files for build types that will not compile.
  # Note: it's set to FORCE so that both CMAKE_BUILD_TYPE and CMAKE_CONFIGURATION_TYPES match up.
  set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "Build configurations to generate." FORCE)
  mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

######################################################################
# Options. These are set up front, so are available when configuring
# the SuperBuild, and hence they must also be passed to the normal
# build. So, look in CMake/Superbuild.cmake to see where they are
# passed to the main build of BARD when doing the Superbuild.
######################################################################
option(BUILD_SHARED_LIBS "Build BARD with shared libraries." ON)
set(BARD_EP_TARBALL_LOCATION "http://cmic.cs.ucl.ac.uk/platform/dependencies")


######################################################################
# Setup the path to load CMake macros, and extra CMake files.
######################################################################
set(CMAKE_MODULE_PATH
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/CMake
    ${CMAKE_SOURCE_DIR}/CMake/CMakeExternals
    ${CMAKE_MODULE_PATH}
   )


######################################################################
# Make sure Git is available.
######################################################################
find_package(Git REQUIRED)
if (WIN32)
  set(GITCOMMAND ${GIT_EXECUTABLE})
endif()


######################################################################
# Find Qt. We need to check for Qt first, before we go ahead and do
# the Superbuild, because VTK needs to know if we have Qt.
######################################################################

set(DESIRED_QT_VERSION 5 CACHE STRING "Pick a version of Qt to use: 4 or 5")

if(DESIRED_QT_VERSION MATCHES 4)
  set(QT4_COMPONENTS QtCore QtGui)
  find_package(Qt4 COMPONENTS ${QT4_COMPONENTS} REQUIRED)
  if(QT_FOUND)
    set(QT_USE_QTTEST 1)
    set(QT_USE_QTXML 1)
    set(QT_USE_QTXMLPATTERNS 1)
    set(QT_USE_PHONON 0)
    include(${QT_USE_FILE})
  endif()
endif()
if(DESIRED_QT_VERSION MATCHES 5)
  set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" CACHE PATH "")
  set(QT5_COMPONENTS Core Gui Widgets WebKitWidgets)
  find_package(Qt5 COMPONENTS ${QT5_COMPONENTS} REQUIRED)
  if(Qt5_DIR)
    get_filename_component(_Qt5_DIR "${Qt5_DIR}/../../../" ABSOLUTE)
    list(FIND CMAKE_PREFIX_PATH "${_Qt5_DIR}" _result)
    if(_result LESS 0)
      set(CMAKE_PREFIX_PATH "${_Qt5_DIR};${CMAKE_PREFIX_PATH}" CACHE PATH "" FORCE)
    endif()
    set(BARD_PREFIX_PATH ${_Qt5_DIR})
  endif()
endif()

if(BUILD_SUPERBUILD)
  set(VTK_QT_ARGS
    -DVTK_QT_VERSION:STRING=${DESIRED_QT_VERSION}
    -DVTK_USE_GUISUPPORT:BOOL=ON
    -DVTK_USE_QVTK_QTOPENGL:BOOL=OFF
    -DVTK_USE_QT:BOOL=ON
    -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
  )
endif()

 
######################################################################
# Now, if required, do the SuperBuild
# If we are doing SuperBuild
#   We configure up to this point (see the return() statement)
#   and then we call SuperBuild.cmake, which builds all the
#   dependencies as CMake ExternalProjects, and then also builds
#   BARD as an ExternalProject. However instead of downloading
#   a tar file, you set the SOURCE_DIR to be THIS project, and force
#   the BUILD_SUPERBUILD flag to be off (to avoid infinite loop).
#
# If we are NOT doing superbuild, then the next statement has no
# effect, and the build goes past this point.
######################################################################

if(BUILD_SUPERBUILD)
  include("CMake/SuperBuild.cmake")
  return()
endif(BUILD_SUPERBUILD)


######################################################################
# End of SuperBuild. Print out where the source and binary folders
# are, just to make it really explicit... well, explicit to the user
# that bothers to read these messages! :-)
######################################################################

message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")


######################################################################
# Add additional entries to the CMAKE_MODULE_PATH, now all externals
# are already built.
######################################################################
set(CMAKE_MODULE_PATH
    ${aruco_DIR}/lib/cmake
    ${CMAKE_MODULE_PATH}
   )


######################################################################
# Force MSVC runtime. Depends on BUILD_SHARED_LIBS
######################################################################
if(MSVC)
  set(variables
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_MINSIZEREL
    CMAKE_C_FLAGS_RELEASE
    CMAKE_C_FLAGS_RELWITHDEBINFO
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_MINSIZEREL
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_RELWITHDEBINFO
  )
  if(BUILD_SHARED_LIBS)
    message(STATUS "Forcing MSVC to use dynamic runtime variables.")
    foreach(variable ${variables})
      if(${variable} MATCHES "/MT")
        string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
      endif()
    endforeach()
  else()
    message(STATUS "Forcing MSVC to use static runtime variables.")
    foreach(variable ${variables})
      if(${variable} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
      endif()
    endforeach()
  endif()
  message(STATUS "Initial build flags:")
  foreach(variable ${variables})
    message(STATUS "  '${variable}': ${${variable}}")
  endforeach()
  message(STATUS "")
endif()


######################################################################
# Find Mandatory External packages
######################################################################

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(OpenCV_FIND_QUIETLY ON)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(aruco REQUIRED)

set(ALL_LIBS)
list(APPEND ALL_LIBS ${aruco_LIBS} ${OpenCV_LIBS} ${VTK_LIBRARIES})

######################################################################
# Output directories, for when compiling, not installing.
######################################################################

configure_file(${CMAKE_SOURCE_DIR}/Doc/Doxygen/bardgroup.pl ${CMAKE_BINARY_DIR}/bardgroup.pl @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/Doc/Doxygen/vxl_doxy.pl ${CMAKE_BINARY_DIR}/vxl_doxy.pl @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/Doc/Doxygen/barddoxygen.pl.in ${CMAKE_BINARY_DIR}/barddoxygen.pl)
configure_file(${CMAKE_SOURCE_DIR}/Doc/Doxygen/doxygen.config.in ${CMAKE_BINARY_DIR}/doxygen.config)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CXX_TEST_PATH ${EXECUTABLE_OUTPUT_PATH})              # Used to control, where to put unit test binaries.
set(BASELINE ${BARD_DATA_DIR}/Baseline)
set(INPUT_DATA ${BARD_DATA_DIR}/Input)
make_directory(${CMAKE_BINARY_DIR}/Testing/Temporary)
set(TEMP ${CMAKE_BINARY_DIR}/Testing/Temporary)

foreach(type LIBRARY RUNTIME ARCHIVE)
  set(output_dir ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_${type}_OUTPUT_DIRECTORY ${output_dir} CACHE INTERNAL "Single output directory for building all libraries.")
  mark_as_advanced(CMAKE_${type}_OUTPUT_DIRECTORY)
endforeach()


#######################################################################
# Set the main install locations.
# These are relative to CMAKE_INSTALL_PREFIX which we MUST NOT touch.
#######################################################################
set(BARD_INSTALL_BASE_DIR ".")
set(BARD_INSTALL_BIN_DIR "bin")
set(BARD_INSTALL_INCLUDE_DIR "include/BARD")
set(BARD_INSTALL_MATLAB_DIR "matlab")
set(BARD_INSTALL_DOC_DIR "doc")
set(BARD_INSTALL_LICENSES_DIR "licenses")
set(BARD_INSTALL_LIB_DIR "bin")

#######################################################################
# Set the main include path, just before generating BARDConfigure.
#######################################################################
include_directories(
  ${CMAKE_SOURCE_DIR}/Code
  )

######################################################################
# Decide what subdirectories we are building, and go and build them.
######################################################################

add_subdirectory(Code)

