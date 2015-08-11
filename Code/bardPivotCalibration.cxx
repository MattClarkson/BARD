/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/

#include <tclap/CmdLine.h>
#include <stdexcept>
#include <cstdlib>
#include <cv.h>
#include <strstream>

#include "bardFileIO.h"

int main(int argc, char** argv)
{
  try
  {
    TCLAP::CmdLine cmd("Basic Augmented Reality Demo - Pivot Calibration", ' ', "0.1");
    TCLAP::ValueArg<std::string> inputArg("i","input","File containing lots of 4x4 matrices.",true,"","string");
    TCLAP::ValueArg<std::string> outputArg("o","output","Output file for (4 x 4) matrix.",true,"","string");
    cmd.add( inputArg );
    cmd.add( outputArg );
    cmd.parse( argc, argv );
    std::string inputFile = inputArg.getValue();
    std::string outputFile = outputArg.getValue();

    // 1. Load all matrices.
    std::vector<cv::Matx44d> matrices = bard::LoadMatricesFromFile(inputFile);
    if (matrices.size())
    {
      std::stringstream oss;
      oss << "Failed to read matrices from file:" << inputFile << std::endl;
      throw new std::runtime_error(oss.str());
    }

    // 2. Declare stuff.
    cv::Matx44d offset;
    double residual = 0;

    // 3. Do pivot calib.

    // 4. Output matrix.
    bard::SaveMatrixToFile(offset, outputFile);

    // 5. Finish up.
    std::cout << "Residual=" << residual << std::endl;
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
