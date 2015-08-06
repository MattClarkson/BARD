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
)

add_executable(bardHelloWorld bardHelloWorld.cxx ${VIDEO_SRCS})
target_link_libraries(bardHelloWorld ${ALL_LIBS})
