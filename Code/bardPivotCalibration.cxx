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
    TCLAP::CmdLine cmd("Basic Augmented Reality Demo - Pivot Calibration", ' ', "0.1");
    TCLAP::ValueArg<std::string> inputArg("i","input","File containing lots of 4x4 matrices.",true,"","string");
    TCLAP::ValueArg<std::string> outputArg("o","output","Output file for (4 x 4) matrix.",true,"","string");
    cmd.add( inputArg );
    cmd.add( outputArg );
    cmd.parse( argc, argv );
    std::string inputFile = inputArg.getValue();
    std::string outputFile = outputArg.getValue();

    // To Do. Implement pivot calibration.

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
