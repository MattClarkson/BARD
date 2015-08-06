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

set(VIDEO_SRCS
  bardVideoSourceInterface.cxx
  bardOpenCVVideoSource.cxx
  bardCalibratedCamera.cxx
)

SET(QT_SOURCES_CPP
bardMainWindow.cxx
bardMainRenderingWidget.cxx
)

SET(QT_SOURCES_H
bardMainWindow.h
bardMainRenderingWidget.h
)

SET(QT_SOURCES_UI
bardMainWindow.ui
)

# Generate QT stuff.
QT4_WRAP_UI(QT_SOURCES_UI_H ${QT_SOURCES_UI} )
QT4_WRAP_CPP(QT_MOC_FILES ${QT_SOURCES_H})
SOURCE_GROUP("Generated Files" FILES ${QT_MOC_FILES})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(bardHelloWorld bardHelloWorld.cxx ${VIDEO_SRCS} ${QT_SOURCES_CPP} ${QT_SOURCES_H} ${QT_SOURCES_UI_H} ${QT_MOC_FILES})
target_link_libraries(bardHelloWorld ${ALL_LIBS})
