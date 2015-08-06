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

#########################################################################################
#
# Usage: bardMacroDefineExternalProjectVariables(project_name version_number)
#
# Defines variables that are needed to set up an external project.
# The proj_DEPENDENCIES variable is set to an empty list. If the project depends
# on other external projects, it needs to be updated after the call of this macro.
#
#########################################################################################

macro(bardMacroDefineExternalProjectVariables project version location)

  set(version_subdir "")
  set(proj ${project})
  set(proj_VERSION ${version})
  set(proj_LOCATION ${location})
  set(proj_CONFIG ${EP_BASE}/${proj}${version_subdir}/cmake)
  set(proj_SOURCE ${EP_BASE}/${proj}${version_subdir}/src)
  set(proj_BUILD ${EP_BASE}/${proj}${version_subdir}/build)
  set(proj_INSTALL ${EP_BASE}/${proj}${version_subdir}/install)
  set(proj_DEPENDENCIES "")
  set(${project}_DEPENDS ${project})

  if (${location} MATCHES "^.*(\\.tar\\.gz|\\.tar\\.bz2)$")
    bardMacroGetChecksum(proj_CHECKSUM ${proj_LOCATION})
  endif()

  set(${project}_VERSION ${version})
  set(${project}_LOCATION ${location})

endmacro()


#########################################################################################
#
# Usage: bardMacroGetChecksum(RESULT_VAR FILE_URI)
#
# Downloads the md5 checksum file for the file and stores the checksum
# in RESULT_VAR. It expects that the checksum file has the same name as
# the original file plus the '.md5' extension.
#
#########################################################################################

macro(bardMacroGetChecksum RESULT_VAR FILE_URI)

  # We expect that the checksum has the name of the original file plus
  # the '.md5' extension.
  set(MD5_FILE_URI "${FILE_URI}.md5")

  # Cuts the host name and directory and keeps the file name only:
  string(REGEX REPLACE ".*/" "" MD5_FILE ${MD5_FILE_URI})

  # Downloads the md5 file:
  file(DOWNLOAD "${MD5_FILE_URI}" "${proj_CONFIG}/src/${MD5_FILE}")

  # Reads the first 32B to the output variable. (MD5 checksums are 128b.)
  file(STRINGS "${proj_CONFIG}/src/${MD5_FILE}" checksum LIMIT_INPUT 32)

  set(${RESULT_VAR} ${checksum})
endmacro(bardMacroGetChecksum)
