/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardFileIO.h"
#include "bardMaths.h"

#include <tclap/CmdLine.h>
#include <stdexcept>
#include <strstream>
#include <cstdlib>
#include <cv.h>

int main(int argc, char** argv)
{
  try
  {
    TCLAP::CmdLine cmd("Basic Augmented Reality Demo - Procrustes Analysis", ' ', "0.1");
    TCLAP::ValueArg<std::string> fixedArg("f","fixed","File containing (n x 3) fixed points.",true,"","string");
    TCLAP::ValueArg<std::string> movingArg("m","moving","File containing (n x 3) moving points.",true,"","string");
    TCLAP::ValueArg<std::string> outputArg("o","output","Output file for (4 x 4) matrix.",true,"","string");
    cmd.add( fixedArg );
    cmd.add( movingArg );
    cmd.add( outputArg );
    cmd.parse( argc, argv );
    std::string fixedFile = fixedArg.getValue();
    std::string movingFile = movingArg.getValue();
    std::string outputFile = outputArg.getValue();

    std::vector<cv::Point3d> fixedPoints = bard::LoadPointsFromFile(fixedFile);
    std::vector<cv::Point3d> movingPoints = bard::LoadPointsFromFile(movingFile);

    if (fixedPoints.size() < 3)
    {
      throw std::runtime_error("Not enough fixed points, need at least 3.");
    }
    if (movingPoints.size() < 3)
    {
      throw std::runtime_error("Not enough moving points, need at least 3.");
    }
    if (fixedPoints.size() != movingPoints.size())
    {
      std::stringstream oss;
      oss << "There are " << fixedPoints.size() << " fixed points and " << movingPoints.size() << " moving points, whereas there should be an equal number of fixed and moving points.";
      throw new std::runtime_error(oss.str());
    }

    // 1. Calculate centroid.
    cv::Point3d pPrime = bard::CalculateCentroid(fixedPoints);  // Arun Equation 4.
    cv::Point3d p      = bard::CalculateCentroid(movingPoints); // Arun Equation 6.

    // 2. Subtract centroid
    std::vector<cv::Point3d> q      = bard::SubtractPointFromPoints(movingPoints, p);     // Arun Equation 7.
    std::vector<cv::Point3d> qPrime = bard::SubtractPointFromPoints(fixedPoints, pPrime); // Arun Equation 8.

    // 3. Calculate cross covariance
    cv::Matx33d H = bard::CalculateCrossCovarianceH(q, qPrime); // Arun Equation 11.

    // 4. Does SVD based alignment
    cv::Matx44d outputMatrix;
    double fre = bard::DoSVDPointBasedRegistration(fixedPoints, movingPoints, H, p, pPrime, outputMatrix);

    // 5. Output matrix.
    bard::SaveMatrixToFile(outputMatrix, outputFile);

    // 6. Finish up.
    std::cout << "FRE=" << fre << std::endl;
    return EXIT_SUCCESS;
  }
  catch (TCLAP::ArgException &e)
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }
  catch (std::runtime_error& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
  }
}
