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
 * \brief Loads a flat text file containing 3 floats (x, y, z coordinates) per line.
 */
std::vector<cv::Point3d> LoadPointsFromFile(const std::string& fileName);

/**
 * \brief Writes the matrix to file, as 4x4 plain-text numbers.
 */
void SaveMatrixToFile(const cv::Matx44d& matrix, const std::string& fileName);

} // end namespace

#endif
