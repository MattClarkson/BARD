/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/

#include <tclap/CmdLine.h>
#include <iostream>
#include <cstdlib>

#include <bardOpenCVVideoSource.h>

int main(int argc, char** argv)
{
  try
  {
    TCLAP::CmdLine cmd("Basic Augmented Reality Demo - Frame Grabber", ' ', "0.1");
    TCLAP::ValueArg<std::string> imageArg("i","image","Filename to write an image to.",true,"","string");
    cmd.add( imageArg );
    cmd.parse( argc, argv );
    std::string imageFile = imageArg.getValue();

    bard::OpenCVVideoSource mySource("");
    mySource.DumpImage(imageFile);
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
