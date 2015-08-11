/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardFileIO_h
#define bardFileIO_h
#include <cv.h>

namespace bard
{

/**
 * \brief Loads a plain-text file containing 3 floats per line (x, y, z coordinates).
 */
std::vector<cv::Point3d> LoadPointsFromFile(const std::string& fileName);

/**
 * \brief Loads a plain-text file containing 4 rows of 4 floats.
 */
cv::Matx44d LoadMatrixFromFile(const std::string& fileName);

/**
 * \brief Writes the matrix to file, as 4x4 plain-text numbers.
 */
void SaveMatrixToFile(const cv::Matx44d& matrix, const std::string& fileName);

/**
 * \brief Loads 3x3 intrinsic and 1x4 distortion parameters.
 */
void LoadCameraParameters(const std::string fileName, cv::Matx33d& intrinsicParameters, cv::Matx14d& distortionParameters);

} // end namespace

#endif
