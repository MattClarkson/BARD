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

int main(int argc, char** argv)
{
  try
  {
    TCLAP::CmdLine cmd("Basic Augmented Reality Demo - Camera Calibration", ' ', "0.1");
    TCLAP::ValueArg<std::string> directoryArg("i","input","Directory containing images of chessboards.",true,"","string");
    TCLAP::ValueArg<std::string> outputArg("o","output","Output file for (4 x 4) matrix.",true,"","string");
    cmd.add( directoryArg );
    cmd.add( outputArg );
    cmd.parse( argc, argv );
    std::string inputDir = directoryArg.getValue();
    std::string outputFile = outputArg.getValue();

    // To Do. Implement camera calibration using standard OpenCV functions.

    return EXIT_SUCCESS;
  }
  catch (TCLAP::ArgException &e)
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
  }
}
