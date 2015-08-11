/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardFileIO.h"

#include <stdexcept>
#include <fstream>
#include <strstream>

namespace bard
{

//-----------------------------------------------------------------------------
std::vector<cv::Point3d> LoadPointsFromFile(const std::string& fileName)
{
  if (fileName.length() == 0)
  {
    throw new std::runtime_error("Empty filename supplied.");
  }
  std::ifstream ifs(fileName.c_str());
  if (!ifs.is_open())
  {
    std::stringstream oss;
    oss << "Failed to open file:" << fileName << std::endl;
    throw new std::runtime_error(oss.str());
  }
  cv::Point3d point;
  std::vector<cv::Point3d> points;
  while (!ifs.eof())
  {
    ifs >> point.x;
    ifs >> point.y;
    ifs >> point.z;
    if (ifs.good())
    {
      points.push_back(point);
    }
  }
  return points;
}


//-----------------------------------------------------------------------------
void SaveMatrixToFile(const cv::Matx44d& matrix, const std::string& fileName)
{
  if (fileName.length() == 0)
  {
    throw new std::runtime_error("Empty filename supplied.");
  }
  std::ofstream ofs(fileName.c_str());
  if (!ofs.is_open())
  {
    std::stringstream errMsg;
    errMsg << "Failed to open file " << fileName << " to write matrix." << std::endl;
    throw std::runtime_error(errMsg.str());
  }
  for (int i = 0; i < 4; i++)
  {
    ofs << matrix(i, 0) << " " << matrix(i, 1) << " " << matrix(i, 2) << " " << matrix(i, 3) << std::endl;
  }
  ofs.close();
}

} // end namespace
