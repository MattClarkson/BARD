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

    // To Do. Implement procrustes analysis.

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
